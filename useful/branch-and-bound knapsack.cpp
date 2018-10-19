// max-profit branch-and-bound knapsack

#include <iostream>
#include <iterator>

using namespace std;

////////////min/////////////
template<class T>
T min(T a, T b)
{
	return (a < b) ? a : b;
}
////////////min/////////////


////////////// 归并排序 ////////////////////
template <class T>
void mergeSort(T a[], int n)
{// Sort a[0 : n - 1] using the merge sort method.
	T *b = new T[n];
	int segmentSize = 1;
	while (segmentSize < n)
	{
		mergePass(a, b, n, segmentSize); // merge from a to b
		segmentSize += segmentSize;
		mergePass(b, a, n, segmentSize); // merge from b to a
		segmentSize += segmentSize;
	}
}

template <class T>
void mergePass(T x[], T y[], int n, int segmentSize)
{// Merge adjacent segments from x to y.
	int i = 0;   // start of the next segment
	while (i <= n - 2 * segmentSize)
	{// merge two adjacent segments from x to y
		merge(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
		i = i + 2 * segmentSize;
	}

	// fewer than 2 full segments remain
	if (i + segmentSize < n)
		// 2 segments remain
		merge(x, y, i, i + segmentSize - 1, n - 1);
	else
		// 1 segment remains, copy to y
		for (int j = i; j < n; j++)
			y[j] = x[j];
}

template <class T>
void merge(T c[], T d[], int startOfFirst, int endOfFirst,
	int endOfSecond)
{// Merge two adjacent segments from c to d.
	int first = startOfFirst,       // cursor for first segment
		second = endOfFirst + 1,    // cursor for second
		result = startOfFirst;      // cursor for result

	// merge until one segment is done
	while ((first <= endOfFirst) && (second <= endOfSecond))
		if (c[first] <= c[second])
			d[result++] = c[first++];
		else
			d[result++] = c[second++];

	// take care of leftovers
	if (first > endOfFirst)
		for (int q = second; q <= endOfSecond; q++)
			d[result++] = c[q];
	else
		for (int q = first; q <= endOfFirst; q++)
			d[result++] = c[q];
}
////////////// 归并排序 ////////////////////

//////////重新申请内存，即扩大内存//////////
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
		cout << "new length must be >= 0" << endl;

	T* temp = new T[newLength];              // new array
	int number = min(oldLength, newLength);  // number to copy
	copy(a, a + number, temp);
	delete[] a;                             // deallocate old memory
	a = temp;
}
//////////重新申请内存，即扩大内存//////////

/////////最大堆/////////////
template<class T>
class maxHeap
{
public:
	maxHeap(int initialCapacity = 10);
	~maxHeap() { delete[] heap; }
	bool empty() const { return heapSize == 0; }
	int size() const
	{
		return heapSize;
	}
	const T& top()
	{// return max element
		if (heapSize == 0)
			cout << "heap size is empty" << endl;
		return heap[1];
	}
	void pop();
	void push(const T&);
	void initialize(T *, int);
	void deactivateArray()
	{
		heap = NULL; arrayLength = heapSize = 0;
	}
	void output(ostream& out) const;
private:
	int heapSize;       // number of elements in queue
	int arrayLength;    // queue capacity + 1
	T *heap;            // element array
};
template<class T>
maxHeap<T>::maxHeap(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		cout << "Initial capacity = " << initialCapacity << " Must be > 0";
	}
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}

template<class T>
void maxHeap<T>::push(const T& theElement)
{// Add theElement to heap.

	// increase array length if necessary
	if (heapSize == arrayLength - 1)
	{// double array length
		changeLength1D(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	// find place for theElement
	// currentNode starts at new leaf and moves up tree
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < theElement)
	{
		// cannot put theElement in heap[currentNode]
		heap[currentNode] = heap[currentNode / 2]; // move element down
		currentNode /= 2;                          // move to parent
	}

	heap[currentNode] = theElement;
}

template<class T>
void maxHeap<T>::pop()
{// Remove max element.
	// if heap is empty return null
	if (heapSize == 0)   // heap empty
		cout << "heap size is empty" << endl;

	// Delete max element
	heap[1].~T();

	// Remove last element and reheapify
	T lastElement = heap[heapSize--];

	// find place for lastElement starting at root
	int currentNode = 1,
		child = 2;     // child of currentNode
	while (child <= heapSize)
	{
		// heap[child] should be larger child of currentNode
		if (child < heapSize && heap[child] < heap[child + 1])
			child++;

		// can we put lastElement in heap[currentNode]?
		if (lastElement >= heap[child])
			break;   // yes

		// no
		heap[currentNode] = heap[child]; // move child up
		currentNode = child;             // move down a level
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template<class T>
void maxHeap<T>::initialize(T *theHeap, int theSize)
{// Initialize max heap to element array theHeap[1:theSize].
	delete[] heap;
	heap = theHeap;
	heapSize = theSize;

	// heapify
	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];

		// find place to put rootElement
		int child = 2 * root; // parent of child is target
		// location for rootElement
		while (child <= heapSize)
		{
			// heap[child] should be larger sibling
			if (child < heapSize && heap[child] < heap[child + 1])
				child++;

			// can we put rootElement in heap[child/2]?
			if (rootElement >= heap[child])
				break;  // yes

			// no
			heap[child / 2] = heap[child]; // move child up
			child *= 2;                    // move down a level
		}
		heap[child / 2] = rootElement;
	}
}

template<class T>
void maxHeap<T>::output(ostream& out) const
{// Put the list into the stream out.
	copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const maxHeap<T>& x)
{
	x.output(out); return out;
}
/////////最大堆/////////////


//// main parameters for knapsack/////////
struct bbNode
{
	// data members
	bbNode* parent;        // pointer to parent node
	bool leftChild;        // true iff left child of parent

	// constructor
	bbNode(bbNode* theParent, bool theLeftChild)
	{
		parent = theParent;
		leftChild = theLeftChild;
	}

};
struct heapNode
{
	// data members
	bbNode* liveNode;
	double upperProfit;
	double profit;
	double weight;
	int upperWeight;    // upper weight of live node
	int level;          // level of live node

	// constructors
	heapNode() {};

	heapNode(bbNode* theLiveNode, double theUpperProfit, double theProfit,
		double theWeight, int theLevel)
	{
		liveNode = theLiveNode;
		upperProfit = theUpperProfit;
		profit = theProfit;
		weight = theWeight;
		level = theLevel;
	}

	bool operator<(const heapNode right)
	{
		return upperProfit < right.upperProfit;
	}

	// type conversion to enable arithmetics etc.
	operator double() { return upperProfit; }
};
struct element
{
	// data members
	int id;   // object identifier
	double profitDensity;

	// constructors
	element() {}

	element(int theID, double theProfitDensity)
	{
		id = theID;
		profitDensity = theProfitDensity;
	}

	operator double() { return profitDensity; }
};

// global variables
double capacity;
int numberOfObjects;
double *weight;
double *profit;
double weightOfCurrentPacking;
double profitFromCurrentPacking;
int *bestPackingSoFar;
maxHeap<heapNode> liveNodeMaxHeap;

double maxProfitBBKnapsack();
void addLiveNode(double, double, double, int, bbNode*, bool);
double profitBound(int);

double knapsack(double *theProfit, double *theWeight, int theNumberOfObjects, double theCapacity, int *bestPacking)
{// theProfit[1:theNumberOfObjects] is array of object profits
	// theWeight[1:theNumberOfObjects] is array of object weights
	// theCapacity is knapsack capacity
	//  bestPacking[1:theNumberOfObjects] is set to best knapsack filling.
	// Return profit of best filling.
	capacity = theCapacity;
	numberOfObjects = theNumberOfObjects;

	// define an element array for profit densities
	element *q = new element[numberOfObjects];

	// set up densities in q[0:numberOfObjects-1] and
	// sum the weights and profits
	double weightSum = 0.0;         // will be sum of weights
	double profitSum = 0.0;         // will be sum of profits
	for (int i = 1; i <= numberOfObjects; i++)
	{
		q[i - 1] = element(i, theProfit[i] / theWeight[i]);
		profitSum += theProfit[i];
		weightSum += theWeight[i];
	}

	if (weightSum <= capacity)   // all objects fit
	{
		fill(bestPacking + 1, bestPacking + numberOfObjects + 1, 1);
		return profitSum;
	}

	// sort into increasing density order, 从小到大排序
	mergeSort(q, numberOfObjects);

	// initialize globals
	profit = new double[numberOfObjects + 1];
	weight = new double[numberOfObjects + 1];
	for (int i = 1; i <= numberOfObjects; i++)
	{// profits and weights in decreasing density order， 从大到小的顺序装入
		profit[i] = theProfit[q[numberOfObjects - i].id];
		weight[i] = theWeight[q[numberOfObjects - i].id];
	}
	weightOfCurrentPacking = 0.0;
	profitFromCurrentPacking = 0.0;
	bestPackingSoFar = new int[numberOfObjects + 1];

	// find best profit and construct packing
	double maxProfit = maxProfitBBKnapsack();
	for (int i = 1; i <= numberOfObjects; i++)
		bestPacking[q[numberOfObjects - i].id] = bestPackingSoFar[i];
	return maxProfit;
}
double maxProfitBBKnapsack()
{// Max-profit branch-and-bound search of solution space tree.
	// Set bestPackingSoFar[i] = 1 iff object i is in knapsack in best filling.
	// Return profit of best knapsack filling.
	// initialize for level 1 start
	bbNode* eNode = NULL;
	int eNodeLevel = 1;
	double maxProfitSoFar = 0.0;
	double maxPossibleProfitInSubtree = profitBound(1);

	// search subset space tree
	while (eNodeLevel != numberOfObjects + 1)
	{// not at leaf
		// check left child
		double weightOfLeftChild = weightOfCurrentPacking
			+ weight[eNodeLevel];
		if (weightOfLeftChild <= capacity)
		{// feasible left child
			if (profitFromCurrentPacking + profit[eNodeLevel]
		> maxProfitSoFar)
		maxProfitSoFar = profitFromCurrentPacking
		+ profit[eNodeLevel];
			addLiveNode(maxPossibleProfitInSubtree,
				profitFromCurrentPacking + profit[eNodeLevel],
				weightOfCurrentPacking + weight[eNodeLevel],
				eNodeLevel + 1, eNode, true);
		}
		maxPossibleProfitInSubtree = profitBound(eNodeLevel + 1);

		// check right child
		if (maxPossibleProfitInSubtree >= maxProfitSoFar)
			// right child has prospects
			addLiveNode(maxPossibleProfitInSubtree,
			profitFromCurrentPacking,
			weightOfCurrentPacking,
			eNodeLevel + 1, eNode, false);

		// get next E-node, heap cannot be empty
		heapNode nextENode = liveNodeMaxHeap.top();
		liveNodeMaxHeap.pop();
		eNode = nextENode.liveNode;
		weightOfCurrentPacking = nextENode.weight;
		profitFromCurrentPacking = nextENode.profit;
		maxPossibleProfitInSubtree = nextENode.upperProfit;
		eNodeLevel = nextENode.level;
	}

	// construct bestPackingSoFar[] by following path
	// from eNode to the root
	for (int j = numberOfObjects; j > 0; j--)
	{
		bestPackingSoFar[j] = (eNode->leftChild) ? 1 : 0;
		eNode = eNode->parent;
	}

	return profitFromCurrentPacking;
}
void addLiveNode(double upperProfit, double theProfit, double theWeight, int theLevel, bbNode* theParent, bool leftChild)
{// Add a new live node to the max heap.
	// Also add the new node to the solution space tree.
	// upperProfit = upper bound on profit for the live node.
	// theProfit = profit of new live node.
	// theWeight = weight of new live node.
	// theLevel = level of live node.
	// theParent = parent of new node.
	// leftChild is true iff new node is left child of theParent.
	// create the new node of the solution space tree
	bbNode* b = new bbNode(theParent, leftChild);

	// put corresponding heap node into max heap
	liveNodeMaxHeap.push(heapNode(b, upperProfit, theProfit,
		theWeight, theLevel));
}
double profitBound(int currentLevel)
{// Bounding function.
	// Return upper bound on value of best leaf in subtree.
	double remainingCapacity = capacity - weightOfCurrentPacking;
	double profitBound = profitFromCurrentPacking;

	// fill remaining capacity in order of profit density
	while (currentLevel <= numberOfObjects &&
		weight[currentLevel] <= remainingCapacity)
	{
		remainingCapacity -= weight[currentLevel];
		profitBound += profit[currentLevel];
		currentLevel++;
	}

	// take fraction of next object
	if (currentLevel <= numberOfObjects)
		profitBound += profit[currentLevel] / weight[currentLevel]
		* remainingCapacity;
	return profitBound;
}
//// main parameters for knapsack/////////


////main function/////
int main()
{
	double p[] = { 0, 6, 3, 5, 4, 6 };
	double w[] = { 0, 2, 2, 6, 5, 4 };
	int n = 5;
	int c = 10;
	int *bestx = new int[n + 1];
	cout << "Optimal value is " << knapsack(p, w, n, c, bestx) << endl;
	cout << "Packing vector is ";
	copy(bestx + 1, bestx + n + 1, ostream_iterator<int>(cout, "  "));
	cout << endl;
	system("pause");
	return 0;
}
