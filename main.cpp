#include <iostream>
using namespace std;

void my_swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

struct MinHeap{
    int *heap_arr;
    int heap_capacity;
    int heap_size;

    MinHeap(int val){
        heap_size = 0;
        heap_capacity = val;
        heap_arr = new int[val];
    }

    void MinHeapify(int i){
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && heap_arr[l] < heap_arr[i]) smallest = l;
        if (r < heap_size && heap_arr[r] < heap_arr[smallest]) smallest = r;
        if (smallest != i){
            my_swap(&heap_arr[i], &heap_arr[smallest]);
            MinHeapify(smallest);
        }
    }

    int parent(int i)   { return (i-1) / 2; }

    int left(int i)     { return (2*i + 1); }

    int right(int i)    { return (2*i + 2); }

    int extractMin(){
        if (heap_size <= 0) return INT_MAX;
        if (heap_size == 1){
            heap_size--;
            return heap_arr[0];
        }
        int root = heap_arr[0];
        heap_arr[0] = heap_arr[heap_size-1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    void insert(int k){
        if (heap_size == heap_capacity){
            cout << "\nError not enough space!!\n";
            return;
        }
        heap_size++;
        int i = heap_size - 1;
        heap_arr[i] = k;

        while (i != 0 && heap_arr[parent(i)] > heap_arr[i]){
            my_swap(&heap_arr[i], &heap_arr[parent(i)]);
            i = parent(i);
        }
    }
};

struct MaxHeap{
    int *heap_arr;
    int heap_capacity;
    int heap_size;

    MaxHeap(int val){
        heap_size = 0;
        heap_capacity = val;
        heap_arr = new int[val];
    }

    void MaxHeapify(int i){
        int l = left(i);
        int r = right(i);
        int biggest = i;
        if (l < heap_size && heap_arr[l] > heap_arr[i])         biggest = l;
        if (r < heap_size && heap_arr[r] > heap_arr[biggest])  biggest = r;
        if (biggest != i){
            my_swap(&heap_arr[i], &heap_arr[biggest]);
            MaxHeapify(biggest);
        }
    }

    int parent(int i)   { return (i-1) / 2; }

    int left(int i)     { return (2*i + 1); }

    int right(int i)    { return (2*i + 2); }

    int getMax()        { return heap_arr[0];}

    int extractMax(){
        if (heap_size <= 0) return INT_MIN;
        if (heap_size == 1){
            heap_size--;
            return heap_arr[0];
        }
        int root = heap_arr[0];
        heap_arr[0] = heap_arr[heap_size-1];
        heap_size--;
        MaxHeapify(0);

        return root;
    }

    void editAt(int i, int new_val){
        heap_arr[i] = new_val;
        while (i != 0 && heap_arr[parent(i)] < heap_arr[i]){
            my_swap(&heap_arr[i], &heap_arr[parent(i)]);
            i = parent(i);
        }
    }

    void insert(int k){
        if (heap_size == heap_capacity){
            cout << "\nError not enough space!!\n";
            return;
        }

        heap_size++;
        int i = heap_size - 1;
        heap_arr[i] = k;

        while (i != 0 && heap_arr[parent(i)] < heap_arr[i]){
            my_swap(&heap_arr[i], &heap_arr[parent(i)]);
            i = parent(i);
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n, o, price, tax, extra_price;
    char flag;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> o;
        MinHeap tax_heap = MinHeap(o);
        MaxHeap price_heap = MaxHeap(o);
        int total_tax = 0;
        for (int j = 0; j < o; j++) {
            std::cin >> flag;
            switch (flag) {
                case 'a': {
                    std::cin >> price >> tax;
                    price_heap.insert(price);
                    tax_heap.insert(tax);
                    break;
                }
                case 'p': {
                    std::cin >> extra_price;
                    price_heap.editAt(0, price_heap.getMax() + extra_price);
                    break;
                }
                default:
                    std::cout << "Wrong input\n";
                break;
            }
        }

        while(price_heap.heap_size) {
            price = price_heap.extractMax();
            tax = tax_heap.extractMin();
            total_tax += price * tax;
            //std::cout<< "Current max Price: " << price<< " and Current Min tax: " << tax << std::endl;

        }std::cout << total_tax << "\n";
    }
    return 0;
}
