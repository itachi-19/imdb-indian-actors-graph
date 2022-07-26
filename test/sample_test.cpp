/*
 * sample_test.cpp
 * Copyright (C) 2022 itachi <itachi@ASUS-G14>
 *
 * Distributed under terms of the MIT license.
 */

#include <bits/stdc++.h>

// Custom Macros
#define printv(x) for (auto it:x) cout << it << ' ';cout << '\n'
#define printa(a, N) for (int i=0; i<N; i++) cout << a[i] << ' '; cout << '\n';
#define printdp(dp, N, M) for (int i=0; i<=N; i++) { for (int j=0; j<=M; j++) cout << dp[i][j] << ' '; cout << '\n';}
#define scan(v, n) v.resize(n); for (int i=0; i<n; i++) cin >> v[i]
#define FOR(i, s, e) for (int i=s; i<e; i++)
#define all(s) s.begin(), s.end()
#define sz(s) s.size()

using namespace std;
using ll = int64_t;

unordered_map<string, bool> visited;
unordered_map<string, vector<string>> mp_adj;

unordered_map<string, vector<string>> mp_movie;
map<pair<string, string>, vector<string>> mp_actors;
vector<string> route;
vector<vector<string>> routes;

void dfs(string u, string target_actor) {
    visited[u] = true;

    if (u == target_actor) {
        routes.push_back(route);
        return;
    }

    for (auto v: mp_adj[u]) {
        if (!visited[v]) {
            route.push_back(v);
            dfs(v, target_actor);
            route.pop_back();
        }
    }
}


void printEdges(vector<string> route) {
    string pre, cur;
    int n = route.size();

    cout << route[0];
    for (int i = 1; i < n; i++) {
        cur = route[i];
        pre = route[i - 1];

        pair<string, string> edge = {pre, cur};
        for (auto movie: mp_actors[edge]) {
           // cout << pre << " and " << cur  << " have acted together in " << movie << endl;
           cout << " --> ("  <<  movie << ") --> " << cur;
        }
    }
    cout << endl;
}

void printRoutes() {
    for (auto route: routes) {
        cout << "-----------" << endl;
        printEdges(route);
        cout << "-----------" << endl << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    mp_movie["M1"] = {"A1","A2", "A3", "A7"};
    mp_movie["M2"] = {"A5","A12", "A17"};
    mp_movie["M3"] = {"A18","A3", "A17"};
    mp_movie["M4"] = {"A7","A2", "A9"};

    for (auto [k, v]: mp_movie) {
        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                mp_actors[{v[i], v[j]}].push_back(k);
                mp_actors[{v[j], v[i]}].push_back(k);
            }
        }

    }

    for (auto [k, v]: mp_actors) {
        string a1 = k.first, a2 = k.second;
        mp_adj[k.first].push_back(k.second);
    }

    route.push_back("A1");

    dfs("A1", "A17");

    for (auto route: routes) {
        for (auto actor: route) cout << actor << ' ';
        cout << endl;
    }
    printRoutes();
    return 0;
}
