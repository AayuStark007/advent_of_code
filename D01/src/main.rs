use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {
    println!("Reading input");

    if let Ok(lines) = read_lines_str("input.txt") {
        let nums: Vec<i32> = lines
            .into_iter()
            .map(|s| s.parse::<i32>())
            .filter_map(Result::ok)
            .collect();

        if let Some((a, b)) = find_pair(nums, &2020) {
            println!("found pair: {}, {}", a, b);
            println!("Part 1: {}", a * b);
        }
    }
}

fn find_pair(list: Vec<i32>, sum: &i32) -> Option<(i32, i32)> {
    let mut diff = HashMap::<i32, i32>::new();
    for num in list.iter() {
        if let Some(_) = diff.get(num) {
            return Some((num.clone(), sum - num));
        }
        diff.insert(sum - num, 1);
    }

    return None;
}

// TODO: move to utils
fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn read_lines_str<P>(filename: P) -> io::Result<Vec<String>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file)
        .lines()
        .collect::<Result<_, _>>()
        .unwrap())
}
