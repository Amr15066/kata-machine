export default function compare(a: BinaryNode<number> | null, b: BinaryNode<number> | null): boolean {
    // remember that the base case always concerns that basic iteration true or false scenario, so lets take it step by step

    // what are the things that would stop us from checking further if this specific instance is true or false?

    // check if both are null
    if (a === null && b === null){ // not a.value in that case because we are checking if the ACTUAL node exists, hence why the | node in the signature of the method above
        return true;
    }

    if (a === null || b === null) { // in that case we already checked if they are equal and null, but what if one of them only is null? (that's also why it has to be in that order, think of recursion as nested if statements)
        return false;
    }

    // no we handled all null issues, we can look into values
    if (a.value != b.value){
        return false;
    }

    // now if it passes all of that (both aren't last children in nodes, and they are equal in value, continue)

    return compare(a.left, b.left) && compare(a.right,b.right) // the original parent node is checked first before 
}