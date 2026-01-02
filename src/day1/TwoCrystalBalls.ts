export default function two_crystal_balls(breaks: boolean[]): number {
    const n = breaks.length;
    const jump = Math.floor(Math.sqrt(n));
    let i = jump
    for (; i<n;i += jump){
        if (breaks[i]){
            break
        }
    }
    const j = i
    i = i- jump +1
    for (; i < j+1 && i < n; i++){
        if (breaks[i]){
            return i
        }
    }
    return -1

    /*
    we have two balls
    first ball hop root n times
    second ball linearly search,
    how do we do second part? basically if we hop and we get it breaks(true)
    the index i becomes our end in that case, we also subtract root n from the jump

    */
}