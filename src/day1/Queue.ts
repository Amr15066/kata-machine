type Node<T> = {
    value: T
    next?: Node<T>
}

export default class Queue<T> {
    public length: number;
    private head?: Node<T>;
    private tail?: Node<T>;

    constructor() {
        this.length= 0;
        this.head = this.tail= undefined;
    }

    enqueue(item: T): void {
        const node = {value: item} as Node<T>;
        this.length++;
        if (!this.tail){
            this.tail = this.head =node;
            return ;
        }

        this.tail.next = node;
        this.tail = node;
    }
    deque(): T | undefined {

        if(!this.head){
            return undefined;
        }
        this.length--; //we now have to keep track of these things, basically "bookmark" this properties (we are the array)
        
        if(this.length ===0){
            this.tail = undefined;
        }
        const h =this.head;
        this.head=this.head.next;
        h.next= undefined; //garbage collector's job to keep track of these things, but we do it for completeness
        return h.value;

    }

    peek(): T | undefined {
        return this.head?.value; //? is the null coalescing operator, if it is not null it returns a value, if it is null returns undefined
    }
}