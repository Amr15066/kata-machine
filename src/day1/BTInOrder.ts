function walk(curr: BinaryNode<number> | null, path: number[]) : number [] {
    //base case
    if (!curr){
        return path
    }

    
    walk(curr.left, path)
    path.push(curr.value)
    walk(curr.right, path)
    return path

}

export default function pre_order_search(head: BinaryNode<number>): number[] {
    return walk(head, []);
}