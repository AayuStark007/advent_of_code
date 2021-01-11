use util::aoc::read_lines;

fn main() {
    println!("Reading input");

    if let Ok(lines) = read_lines("input.txt") {
        let mut pos: usize = 0;
        let n_tree = lines
            .filter_map(Result::ok)
            .filter(|x| advance_pos(x, &mut pos))
            .count();

        println!("Part 1: {}", n_tree);
    }
}

fn advance_pos(line: &String, pos: &mut usize) -> bool {
    let result = line.chars().nth(*pos).unwrap() == '#';
    *pos = (*pos + 3) % line.len();
    return result;
}
