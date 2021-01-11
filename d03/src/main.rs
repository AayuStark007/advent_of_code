use util::aoc::read_lines;

fn main() {
    println!("Reading input");

    if let Ok(lines) = read_lines("input.txt") {
        let mut pos: usize = 0;
        let mut n_tree: usize = 0;
        for line in lines {
            let line_str = match line {
                Ok(line_str) => line_str,
                Err(e) => panic!(e),
            };
            if advance_pos(&line_str, &mut pos) {
                n_tree += 1;
            }
        }

        println!("Part 1: {}", n_tree);
    }
}

fn advance_pos(line: &String, pos: &mut usize) -> bool {
    let result = line.chars().nth(*pos).unwrap() == '#';
    *pos = (*pos + 3) % line.len();
    return result;
}
