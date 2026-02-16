const dir = [
    [0,-1],
    [1,0],
    [0,1],
    [-1,0]
]

function walk(maze: string [], wall: string,  end: Point, curr: Point, path: Point[], seen: boolean[][]): boolean { //boolean[][] it is a 2D array of boolean stuff 

    // base case
    if (curr.x < 0 || curr.x >= maze[0].length ||
        curr.y < 0 || curr.y >= maze.length){
        return false;
    }
    
    if (maze[curr.y][curr.x] === wall){ 
        return false;
    }

    if (curr.x === end.x && curr.y === end.y){ curr === end
        path.push(end)
        return true;
    }
    
    if (seen[curr.y][curr.x]){
        return false;
    }

    // pre conditions
    seen[curr.y][curr.x]= true;
    path.push(curr)
    // recursion
    for (let i = 0; i < dir.length; i++){
        const [x,y]= dir[i]; //
        if (walk(maze, wall, end, {x: curr.x + x, y: curr.y + y}, path, seen))
            {
                return true;
            }
    }

    // post recursion
    path.pop();
    return false; 
    


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