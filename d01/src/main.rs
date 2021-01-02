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

        // Part 1 solution
        if let Some((a, b)) = find_pair(&nums, &2020) {
            println!("found pair: {}, {}", a, b);
            println!("Part 1: {}", a * b);
        }

        // Part 2 solution

        // create diff map for each entry
        // filter the entry from list
        // find pair for the diff in the filtered map

        for num in nums.iter() {
            let rem_sum = 2020 - num;
            let num_filtered: Vec<i32> = nums.clone().into_iter().filter(|&n| n != *num).collect();
            if let Some((a, b)) = find_pair(&num_filtered, &rem_sum) {
                println!("found triplet: {}, {}, {}", num, a, b);
                println!("Part 2: {}", num * a * b);
                break;
            }
        }
    }
}

fn find_pair(list: &Vec<i32>, sum: &i32) -> Option<(i32, i32)> {
    let mut diff = HashMap::<i32, i32>::new();
    for num in list.iter() {
        if let Some(_) = diff.get(num) {
            return Some((num.clone(), sum - num));
        }
        diff.insert(sum - num, 1);
    }

    return None;
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
