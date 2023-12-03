use std::{error::Error, path::Path};

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

    let r1_d1 = tree_collisions_for_trajectory("input.txt", 1, 1).unwrap();
    let r3_d1 = tree_collisions_for_trajectory("input.txt", 3, 1).unwrap();
    let r5_d1 = tree_collisions_for_trajectory("input.txt", 5, 1).unwrap();
    let r7_d1 = tree_collisions_for_trajectory("input.txt", 7, 1).unwrap();
    let r1_d2 = tree_collisions_for_trajectory("input.txt", 1, 2).unwrap();

    let result = r1_d1 * r3_d1 * r5_d1 * r7_d1 * r1_d2;

    println!("Part 2: {}", result);
}

fn advance_pos(line: &String, pos: &mut usize) -> bool {
    let result = line.chars().nth(*pos).unwrap() == '#';
    *pos = (*pos + 3) % line.len();
    return result;
}

// TODO: use a struct based approach to maintain state
fn advance_pos_with_offset(
    line: &String,
    right: &usize,
    down: &usize,
    pos: &mut usize,
    offset: &mut usize,
) -> bool {
    let mut result = line.chars().nth(*pos).unwrap() == '#';

    // we dont count collisions in intermediate
    if *offset != *down - 1 {
        result = false;
    }

    // if we have completed all downward moves, now we move right for next line
    if *offset == 0 {
        *pos = (*pos + *right) % line.len();
        *offset = *down - 1;
    } else {
        // else we do a down move
        *offset -= 1;
    }

    return result;
}

fn tree_collisions_for_trajectory<P>(
    filename: P,
    right: usize,
    down: usize,
) -> Result<usize, Box<dyn Error>>
where
    P: AsRef<Path>,
{
    let lines = match read_lines(filename) {
        Ok(lines) => lines,
        Err(e) => return Err(Box::new(e)),
    };

    let mut pos: usize = 0;
    let mut offset: usize = down - 1;

    let n_tree = lines
        .filter_map(Result::ok)
        .filter(|x| advance_pos_with_offset(x, &right, &down, &mut pos, &mut offset))
        .count();

    Ok(n_tree)
}
