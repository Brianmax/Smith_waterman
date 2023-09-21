#include<bits/stdc++.h>
using namespace std;
int dp[2000][2000] = {0};
string s1, s2;
int m, n;
int match_value = 1, mismatch_value = -1, gap_value = -2;
vector<pair<int, int>> max_indexes;
// smith waterman algorithm
void smith_waterman(){
    int max_score = 0;
    int S=0;
    
    for(int i=1; i<m; i++){
        for(int j=1; j<n; j++){
            if(s1[i-1]==s2[j-1]){
                S = match_value; 
            }
            else{
                S = mismatch_value;
            }
            dp[i][j] = max(0, max(dp[i-1][j-1]+S, max(dp[i-1][j]+gap_value, dp[i][j-1]+gap_value)));
            if(dp[i][j]>max_score){
                max_score = dp[i][j];
                max_indexes.clear();
                max_indexes.push_back(make_pair(i, j));
            }
            else if(dp[i][j]==max_score){
                max_indexes.push_back(make_pair(i, j));
            }
        }
    }
}
// traceback all maximum scores
vector<pair<string, string>> traceback(){
    vector<pair<string, string>> alignments;
    for (const auto& maxPos : max_indexes) {
        int i = maxPos.first;
        int j = maxPos.second;
        string alignmentA, alignmentB;
        
        while (i > 0 && j > 0 && dp[i][j] != 0) {
            int score = dp[i][j];
            int scoreDiagonal = dp[i-1][j-1];
            int scoreUp = dp[i-1][j];
            int scoreLeft = dp[i][j-1];
            
            if (score == scoreDiagonal + (s1[i-1] == s2[j-1] ? match_value : mismatch_value)) {
                alignmentA = s1[i-1] + alignmentA;
                alignmentB = s2[j-1] + alignmentB;
                i--;
                j--;
            } else if (score == scoreUp + gap_value) {
                alignmentA = s1[i-1] + alignmentA;
                alignmentB = "-" + alignmentB;
                i--;
            } else if (score == scoreLeft + gap_value) {
                alignmentA = "-" + alignmentA;
                alignmentB = s2[j-1] + alignmentB;
                j--;
            }
        }
        
        alignments.push_back({alignmentA, alignmentB});
    }
    return alignments;
    
}
int main(){

    // test case 1
    s1 = "tcaagcgttagagaagtcattatgtgataaaaaaattcaacttggtatcaacttaactaagggtcttggtgctggtgctttgcctgatgttggtaaaggtgcagcagaagaatcaattgatgaaattatggagcatataaaagatagccatatgctctttatcacagcagggatgggtggtggtactggaacaggtgctgcaccggtaattgcaaaagcagccagagaagcaagagcggtagttaaagataaaggagcaaaagaaaaaaagatactgactgttggagttgtaactaagccgttcggttttgaaggtgtgcgacgtatgcgcattgcagagcttggacttgaagagttgcaaaaatacgtagatacacttattgtcattcccaatcaaaatttatttagaattgctaacgagaaaactacatttgctgacgcatttcaactcgccgataatgttctgcatattggcataagaggagtaactgatttgatgatcatgccaggactgattaatcttgattttgctgatatagaaacagtaatgagtgagatgggtaaagcaatgattggtactggagaggcagaaggagaagatagggcaattagcgctgcagaggctgcgatatctaatccattacttgataatgtatcaatgaaaggtgcacaaggaatattaattaatattactggtggtggagatatgactctatttgaagttgatgctgcagccaatagagtgcgtgaagaagtcgatgaaaatgcaaatataatatttggtgccacttttgatcaggcgatggaaggaagagttagagtttctattcttgcaactggcattgatagctgtaacgacaattcatctgttaatcaaaacaagatcccagcagaggaaaaaaattttaaatggccttataatcaagttcctatatcagaaacaaaagaatatgcttcaactgagcaaacaaacgaaagagttaagtggggcagcaatgtttatgatataccagcttatctaagaagaaaaaaataatgcaattttggctactcaagtcgg";
    s2 = "attaaaggtttataccttcccaggtaacaaaccaaccaactttcgatctcttgtagatctgttctctaaacgaactttaaaatctgtgtggctgtcactcggctgcatgcttagtgcactcacgcagtataattaataactaattactgtcgttgacaggacacgagtaactcgtctatcttctgcaggctgcttacggtttcgtccgtgttgcagccgatcatcagcacatctaggtttcgtccgggtgtgaccgaaaggtaagatggagagccttgtccctggtttcaacgagaaaacacacgtccaactcagtttgcctgttttacaggttcgcgacgtgctcgtacgtggctttggagactccgtggaggaggtcttatcagaggcacgtcaacatcttaaagatggcacttgtggcttagtagaagttgaaaaaggcgttttgcctcaacttgaacagccctatgtgttcatcaaacgttcggatgctcgaactgcacctcatggtcatgttatggttgagctggtagcagaactcgaaggcattcagtacggtcgtagtggtgagacacttggtgtccttgtccctcatgtgggcgaaataccagtggcttaccgcaaggttcttcttcgtaagaacggtaataaaggagctggtggccatagttacggcgccgatctaaagtcatttgacttaggcgacgagcttggcactgatccttatgaagattttcaagaaaactggaacactaaacatagcagtggtgttacccgtgaactcatgcgtgagcttaacggaggggcatacactcgctatgtcgataacaacttctgtggccctgatggctaccctcttgagtgcattaaagaccttctagcacgtgctggtaaagcttcatgcactttgtccgaacaactggactttattgacactaagaggggtgtatactgctgccgtgaacatgagcatgaaattgcttggtacacggaacgttctgaaaagagctatgaattgcagacaccttttgaaattaaattggcaaagaaatttgacaccttcaatggggaatgtccaaa";
    m = s1.length()+1;
    n = s2.length()+1;
    smith_waterman();
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"------------------"<<endl;
    /* for(int i=0; i<max_indexes.size(); i++){
        cout<<max_indexes[i].first<<" "<<max_indexes[i].second<<endl;
        cout<<dp[max_indexes[i].first][max_indexes[i].second]<< endl;
    } */
    vector<pair<string, string>> alignments = traceback();
    for (const auto& alignment : alignments) {
        cout << "       " << alignment.first << endl;
        cout << "       " <<alignment.second << endl;
        cout << endl;
    }
    return 0;
}