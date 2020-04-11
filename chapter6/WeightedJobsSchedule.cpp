#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// create the struct to store job information
struct job {
    int startTime, endTime, weight;
};

// help function for sorting
bool compareJob(job& job1, job& job2) {
    return (job1.endTime < job2.endTime);
}

// find the non-conflict job
vector<int> findNonConflict(const vector<job>& jobs) {
    int length = jobs.size();
    vector<int> nonConflict(jobs.size());
    for (int current_job = length-1; current_job >= 0; current_job--) {
        for (int i = current_job - 1; i >= 0; i--) {
            if (jobs[current_job].startTime > jobs[i].endTime) {
                nonConflict[current_job] = i;
                break; 
            }
        }
    }

    return nonConflict;
}

void computeOpt(int index, vector<job>& jobs, const vector<int>& nonConflict, vector<int>& preComputed) {
    if (index == 0)
        return;
    
    if (preComputed[index] != 0)
        return;
    else {
        preComputed[index] = max(jobs[index].weight + preComputed[nonConflict[index]], preComputed[index-1]);
        return;
    }
}

void findSolution(const vector<job>& jobs, const vector<int>& nonConflict, const vector<int>& preComputed) {
    int total_benifit = 0;
    for (int i = jobs.size(); i >= 0;) {
        if (jobs[i].weight + preComputed[nonConflict[i]] > preComputed[i-1]) {
            cout << "Job number: " << i << " benifit: " << jobs[i].weight << endl;
            total_benifit += jobs[i].weight;
            if (i == 0)
                break;
            i = nonConflict[i];
        } else {
            i--;
        }
    }

    cout << "Total benifit: " << total_benifit << endl;
}

// get the maximum benift from the give jobs
void findMaxBenifit(vector<job>& jobs) {
    // first sort jobs
    sort(jobs.begin(), jobs.end(), compareJob);

    // find the non-conflict job
    vector<int> indexOfNonConflict = findNonConflict(jobs);
    vector<int> preComputed(jobs.size());

    for (int i = 0; i < jobs.size(); i++) {
        computeOpt(i, jobs, indexOfNonConflict, preComputed);
    }

    findSolution(jobs, indexOfNonConflict, preComputed);
}

int main() {
    vector<job> jobs = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};

    findMaxBenifit(jobs);

    return 0;
}