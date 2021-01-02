use util::aoc::{find_pair, read_lines_str};

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
