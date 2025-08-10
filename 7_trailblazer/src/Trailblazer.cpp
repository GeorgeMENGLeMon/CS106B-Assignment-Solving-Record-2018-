// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "Trailblazer.h"
#include "queue.h"
#include "hashset.h"
#include "pqueue.h"
#include <limits>
#include "hashmap.h"
#include "functional"

using namespace std;
static const double SUFFICIENT_DIFFERENCE = 0.2;

Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    Queue<RoadNode*> queue;
    HashSet<RoadNode*> visited;
    HashMap<RoadNode*, RoadNode*> backtrack;

    queue.enqueue(start);
    start->setColor(Color::YELLOW);
    visited.add(start);

    while(!queue.isEmpty()) {
        RoadNode* v = queue.dequeue();
        v->setColor(Color::GREEN);
        if(v == end) {
            Path path;
            for(RoadNode* i = end ; i != nullptr ; i = backtrack[i])
                path.add(i);
            path.reverse();
            return path;
        }

        for(RoadNode* n : graph.neighborsOf(v)) {
            if(!visited.contains(n)) {
                queue.enqueue(n);
                visited.add(n);
                n->setColor(Color::YELLOW);
                backtrack[n] = v;
            }
        }
    }
    return {};
}

Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    // Get all nodes
    HashSet<RoadNode*> allNodes;
    Queue<RoadNode*> q;
    allNodes.add(start);
    q.enqueue(start);
    while(!q.isEmpty()) {
        RoadNode* v = q.dequeue();
        for(RoadNode* n : graph.neighborsOf(v))
            if(!allNodes.contains(n)) {
                allNodes.add(n);
                q.enqueue(n);
            }
    }

    // Initialization
    HashMap<RoadNode*, double> cost;
    for(RoadNode* node : allNodes)
        cost[node] = numeric_limits<double>::infinity();
    cost[start] = 0.0;

    PriorityQueue<RoadNode*> pq;
    HashSet<RoadNode*> visited;
    HashMap<RoadNode*, RoadNode*> backtrack;
    pq.enqueue(start,cost[start]);
    start->setColor(Color::YELLOW);

    while(!pq.isEmpty()) {
        RoadNode* v = pq.dequeue();
        if(visited.contains(v)) continue;
        visited.add(v);
        v->setColor(Color::GREEN);

        if(v == end) {
            Path path;
            for(RoadNode* i = end ; i != nullptr ; i = backtrack[i])
                path.add(i);
            path.reverse();
            return path;
        }

        for(RoadNode* n : graph.neighborsOf(v)) {
            if(!visited.contains(n)) {
                if(cost[v]+ graph.edgeBetween(v,n)->cost() < cost[n]) {
                    cost[n] = cost[v]+ graph.edgeBetween(v,n)->cost();
                    pq.enqueue(n,cost[n]);
                    n->setColor(Color::YELLOW);
                    backtrack[n] = v;
                }
            }
        }
    }
    return {};
}

Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    HashSet<RoadNode*> allNodes;
    Queue<RoadNode*> q;
    allNodes.add(start);
    q.enqueue(start);
    while(!q.isEmpty()) {
        RoadNode* v = q.dequeue();
        for(RoadNode* n : graph.neighborsOf(v)) {
            if(!allNodes.contains(n)) {
                allNodes.add(n);
                q.enqueue(n);
            }
        }

    }

    HashMap<RoadNode*, double> cost;
    for(RoadNode* node : allNodes)
        cost[node] = numeric_limits<double>::infinity();
    cost[start] = 0.0 ;

    function<double(RoadNode*, RoadNode*)> Heuristic = [&](RoadNode* a,RoadNode* b) {
            return graph.crowFlyDistanceBetween(a,b) / graph.maxRoadSpeed();

    };

    PriorityQueue<RoadNode*> pq;
    HashSet<RoadNode*> visited;
    HashMap<RoadNode*, RoadNode*> backtrack;
    pq.enqueue(start,cost[start] + Heuristic(start,end));
    start->setColor(Color::YELLOW);
    while(!pq.isEmpty()) {
        RoadNode* v = pq.dequeue();
        if(visited.contains(v)) continue;
        visited.add(v);
        v->setColor(Color::GREEN);

        if(v == end) {
            Path path;
            for(RoadNode* i = end ; i != nullptr ; i = backtrack[i ])
                path.add(i);
            path.reverse();
            return path;
        }

        for(RoadNode* n : graph.neighborsOf(v)) {
            if(!visited.contains(n)) {
                if(cost[v] + graph.edgeBetween(v,n)->cost() < cost[n]) {
                    cost[n] = cost[v] + graph.edgeBetween(v,n)->cost();
                    pq.enqueue(n,cost[n] + Heuristic(n,end));
                    n->setColor(Color::YELLOW);
                    backtrack[n] = v;
                }
            }
        }
    }
    return {};
}

Path alternativeRoute(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    HashSet<RoadNode*> allNodes;
    Queue<RoadNode*> q;
    allNodes.add(start);
    q.enqueue(start);
    while(!q.isEmpty()) {
        RoadNode* v = q.dequeue();
        for(RoadNode* n : graph.neighborsOf(v)) {
            if(!allNodes.contains(n)) {
                allNodes.add(n);
                q.enqueue(n);
            }
        }

    }

    function<double(RoadNode*, RoadNode*)> Heuristic = [&](RoadNode* a,RoadNode* b) {
        return graph.crowFlyDistanceBetween(a,b) / graph.maxRoadSpeed();

    };

    struct Path_Cost {
        Path path;
        double cost;

        Path_Cost() {
            path = {};
            cost = numeric_limits<double>::infinity();
        }

        Path_Cost(const Path& p, double c) : path(p), cost(c) {}
    };

    function<Path_Cost(RoadNode*, RoadNode*)> Astar = [&](RoadNode* a, RoadNode* b) {
        HashMap<RoadNode*, double> cost;
        for(RoadNode* node : allNodes)
            cost[node] = numeric_limits<double>::infinity();
        cost[start] = 0.0 ;

        PriorityQueue<RoadNode*> pq;
        HashSet<RoadNode*> visited;
        HashMap<RoadNode*, RoadNode*> backtrack;
        pq.enqueue(start,cost[start] + Heuristic(start,end));
        start->setColor(Color::YELLOW);
        while(!pq.isEmpty()) {
            RoadNode* v = pq.dequeue();
            if(visited.contains(v)) continue;
            visited.add(v);
            v->setColor(Color::GREEN);

            if(v == end) {
                Path path;
                for(RoadNode* i = end ; i != nullptr ; i = backtrack[i ])
                    path.add(i);
                path.reverse();
                return Path_Cost{path,cost[end]};
            }

            for(RoadNode* n : graph.neighborsOf(v)) {
                if(!visited.contains(n)) {
                    if((v==a && n==b) || (v==b && n==a)) continue;
                    if(cost[v] + graph.edgeBetween(v,n)->cost() < cost[n]) {
                        cost[n] = cost[v] + graph.edgeBetween(v,n)->cost();
                        pq.enqueue(n,cost[n] + Heuristic(n,end));
                        n->setColor(Color::YELLOW);
                        backtrack[n] = v;
                    }
                }
            }
        }
        return Path_Cost{};
    };
    Path_Cost minPath = Astar(nullptr, nullptr); // In this program node can not be a nullpter
    HashSet<RoadEdge*> edges;
    for(int i = 0 ; i < minPath.path.size() - 1 ; i ++)
        edges.add(graph.edgeBetween(minPath.path[i],minPath.path[i+1]));

    function<bool(const Path&, const Path&)> Difference = [&](const Path& P, const Path& B) {
        int numer = 0;
        for(RoadNode* node : P) {
            if(!B.contains(node) && P.contains(node)) numer ++;
        }
        double diff = double(numer) / B.size();
        return diff > SUFFICIENT_DIFFERENCE;
    };

    Path_Cost result {};
    for(RoadEdge* edge : edges) {
        Path_Cost B = Astar(edge->from(),edge->to());
        if(Difference(minPath.path,B.path) && B.cost <= result.cost && B.cost != numeric_limits<double>::infinity())
            result = B;
    }
    return result.path;
}


/*

Possible Extra Features
Though your solution to this assignment must match all of the specifications mentioned previously, you are allowed and encouraged to add extra features to your program if you’d like. Here are some ideas for extra features that you could add.

1.Implement bidirectional search: A common alternative to using A* search is to use a bidirectional search algorithm, in which you search outward from both the start and end vertices simultaneously. As soon as the two searches find a vertex in common, you can construct a path from the start vertex to the end vertex by joining the two paths to that vertex together. Try coding this algorithm up as a fifth algorithm choice.

2.Better alternate: The alternate route algorithm is slow and not guaranteed to find the best alternate. Can you come up with a different algorithm that is faster or that uses a more realistic measure of path distance?
    a. K-Shortest Paths: en’s Algorithm、Eppstein’s Algorithm
    b. Penalty-based Methods
    c. Multi-criteria Optimization
    d. Dissimilarity Constraints

3.Add more data from open maps: We generated the maps from openstreetmaps.org. In the graphs you see, we added some nodes and edges, but left out a lot of interesting information (like street names and buildings). Here is a link to a folder with all of the raw openstreetmap data. Do anything you like with it. Can you print out directions? We haven’t tried yet but it seems interesting!

4.Other: If you have your own creative idea for an extra feature, go for it!

*/

Path bidirectional_breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    if(start == end) return {};

    Queue<RoadNode*> qStart,qEnd;
    HashSet<RoadNode*> vStart,vEnd;
    HashMap<RoadNode*, RoadNode*> bStart,bEnd;

    Queue<RoadNode*>* queue;
    HashSet<RoadNode*>* visited;
    HashSet<RoadNode*>* otherVisited;
    HashMap<RoadNode*, RoadNode*>* backtrack;
    HashMap<RoadNode*, RoadNode*>* otherBacktrack;

    qStart.enqueue(start);
    qEnd.enqueue(end);
    start->setColor(Color::YELLOW);
    end->setColor(Color::YELLOW);
    vStart.add(start);
    vEnd.add(end);
    bool transver = true;

    while(!qStart.isEmpty() && !qEnd.isEmpty()) {
        if(transver == true) {
            queue = &qStart;
            visited = &vStart;
            backtrack = &bStart;
            otherVisited = &vEnd;
            otherBacktrack = &bEnd;
        }
        else {
            queue = &qEnd;
            visited = &vEnd;
            backtrack = &bEnd;
            otherVisited = &vStart;
            otherBacktrack = &bStart;
        }
        transver = !transver;

        RoadNode* v = (*queue).dequeue();
        v->setColor(Color::GREEN);

        for(RoadNode* n : graph.neighborsOf(v)) {
            if((*otherVisited).contains(n)) {
                Path path;
                for(RoadNode* i = v ; i != nullptr ; i = transver ? (*otherBacktrack)[i]:(*backtrack)[i])
                    path.add(i);
                path.reverse();

                for(RoadNode* i = n ; i != nullptr ; i = !transver ? (*otherBacktrack)[i]:(*backtrack)[i])
                    path.add(i);
                return path;
            }
            if(!(*visited).contains(n)) {
                (*queue).enqueue(n);
                (*visited).add(n);
                n->setColor(Color::YELLOW);
                (*backtrack)[n] = v;
            }
        }
    }
    return {};
}
