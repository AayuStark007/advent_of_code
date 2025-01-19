use util::aoc::read_lines_str;
use std::collections::{BinaryHeap, HashMap};

fn main() {
    println!("Read input");

    if let Ok(lines) = read_lines_str("input.txt") {
        let mut heap1 = BinaryHeap::new();
        let mut heap2 = BinaryHeap::new();
        for line in lines.iter() {
            let mut iter = line.split_whitespace();
            let num = iter.next().unwrap().parse::<i32>().unwrap();
            heap1.push(num);
            let num2 = iter.next().unwrap().parse::<i32>().unwrap();
            heap2.push(num2);
        }

        let mut total_distance = 0;
        // while binary heap is not empty
        while !heap1.is_empty() {
            let num1 = heap1.pop().unwrap();
            let num2 = heap2.pop().unwrap();
            let distance = (num1 - num2).abs();
            total_distance += distance;
        }

        println!("Total distance: {}", total_distance);
    }

    if let Ok(lines) = read_lines_str("input.txt") {
        // hashmap
        let mut map: HashMap<i32, i32> = HashMap::new();
        let mut list = Vec::new();
        for line in lines.iter() {
            let mut iter = line.split_whitespace();
            let num1 = iter.next().unwrap().parse::<i32>().unwrap();
            let num2 = iter.next().unwrap().parse::<i32>().unwrap();
            list.push(num1);

            let freq: &mut i32 = map.entry(num2).or_insert(0);
            *freq += 1;
        }

        let mut similarity: u32 = 0;
        for num in list.iter() {
            if map.contains_key(num) {
                let freq = map.get(num).unwrap();
                similarity += (*num as u32) * (*freq as u32);
            }
        }

        println!("Similarity: {}", similarity);        
    }
}
