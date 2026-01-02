const dir = [
    { x: 0, y: -1 }, // up
    { x: 1, y: 0 },  // right
    { x: 0, y: 1 },  // down
    { x: -1, y: 0 }  // left
];


function walk(maze:): boolean {
    /*we need to consider base case first
    imagine a block, we can go up down lefto r right, so that is the loop, RECURSIVE NOT BASE
    what we can do iis check if it is out of bounds
    check if it is a wall
    check if it is the end
    check if it is already visited
    */
}
export default function solve(maze: string[], wall: string, start: Point, end: Point): Point[] {

}