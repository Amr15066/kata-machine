const dir: [
   [0,-1],
   [1,0],
   [0,1],
   [-1,0]
]

function walk(maze: string[], wall: string, curr: Point, end: Point, path: Point[], seen: Boolean[][]): boolean {
    // base cases
    //if it leaves the map
    if (curr.x < 0 || curr.x >= maze[0].length ||
        curr.y < 0 || curr.y >= maze.length){
            return false
        }
    
    if (maze[curr.y][curr.x]=== wall){
        return false 
    }
    
    if (curr.x === end.x && curr.y === end.y){
        path.push(end)
        return true
    }

    if (seen[curr.y][curr.x]){
        return false
    }

    //Pre recursion phase

    path.push(curr)
    seen[curr.y][curr.x] = true

    // recursion phase
    for (let i = 0; i < dir.length; i++){
        const [x,y] = dir[i]
        walk(maze, wall, {x: curr.x + x, y: curr.y+y})
    }

}
export default function solve(maze: string[], wall: string, start: Point, end: Point): Point[] {
    const seen: boolean[][]=[];
    const path: Point[] = [] ;
    for (let i = 0; i < maze.length; i++){
        seen.push(new Array(maze[i].length).fill(false));
    }
    walk(maze, wall, end, start, path, seen);
    return path;

}