#include "SCC.h"

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

// A recursive function that finds and prints strongly connected
// components using DFS traversal
// u --> The vertex to be visited next
// disc[] --> Stores discovery times of visited vertices
// low[] -- >> earliest visited vertex (the vertex with minimum
//             discovery time) that can be reached from subtree
//             rooted with current vertex
// *st -- >> To store all the connected ancestors (could be part
//           of SCC)
// stackMember[] --> bit/index array for faster check whether
//                  a node is in stack
void Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st,
	bool stackMember[], vector<Line> line_array, vector<Line>* merged_line_array)
{
	// A static variable is used for simplicity, we can avoid use
	// of static variable by passing a pointer.
	static int time = 0;

	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;
	st->push(u);
	stackMember[u] = true;

	// Go through all vertices adjacent to this
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;  // v is current adjacent of 'u'

					 // If v is not visited yet, then recur for it
		if (disc[v] == -1)
		{
			SCCUtil(v, disc, low, st, stackMember, line_array, merged_line_array);

			// Check if the subtree rooted with 'v' has a
			// connection to one of the ancestors of 'u'
			// Case 1 (per above discussion on Disc and Low value)
			low[u] = min(low[u], low[v]);
		}

		// Update low value of 'u' only of 'v' is still in stack
		// (i.e. it's a back edge, not cross edge).
		// Case 2 (per above discussion on Disc and Low value)
		else if (stackMember[v] == true)
			low[u] = min(low[u], disc[v]);
	}

	// head node found, pop the stack and print an SCC
	int w = 0;  // To store stack extracted vertices
	if (low[u] == disc[u])
	{
		Point3d m_p1 = (0., 0., 0.);
		Point3d m_p2 = (0., 0., 0.);
		int count = 0;
		double dist = 0.;

		while (st->top() != u)
		{
			w = (int)st->top();
			//cout << w << " ";
			stackMember[w] = false;
			st->pop();

			m_p1 += line_array[w].p1;
			m_p2 += line_array[w].p2;
			count += 1;
		}
		w = (int)st->top();
		//cout << w << "n";
		stackMember[w] = false;
		st->pop();

		m_p1 = m_p1 / float(count);
		m_p2 = m_p2 / float(count);
		//print "count : ", count;

		//print v.follow_line

		extern int mergeLineIndex;
		
		Line meanLine = Line( m_p1.x, m_p1.y, m_p2.x, m_p2.y, mergeLineIndex);
		//print "M_line:", m_line.p1;

		//cv2.line(src, (int(_x1), int(_y1)), (int(_x2), int(_y2)), clr, 2);
		merged_line_array->push_back(meanLine);
		mergeLineIndex += 1;
		//printf("%d\n", mergeLineIndex);
	}
}

// The function to do DFS traversal. It uses SCCUtil()
vector<Line> Graph::SCC(vector<Line> line_array)
{
	vector<Line> merged_line_array;
	int *disc = new int[V];
	int *low = new int[V];
	bool *stackMember = new bool[V];
	stack<int> *st = new stack<int>();

	// Initialize disc and low, and stackMember arrays
	for (int i = 0; i < V; i++)
	{
		disc[i] = NIL;
		low[i] = NIL;
		stackMember[i] = false;
	}

	// Call the recursive helper function to find strongly
	// connected components in DFS tree with vertex 'i'
	for (int i = 0; i < V; i++)
		if (disc[i] == NIL)
			SCCUtil(i, disc, low, st, stackMember, line_array, &merged_line_array);

	return merged_line_array;
}
