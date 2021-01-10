use util::aoc::read_lines_str;

use lazy_static::lazy_static;
use regex::Regex;

fn main() {
    println!("Reading input");

    if let Ok(lines) = read_lines_str("input.txt") {
        let valid_count: usize = lines
            .into_iter()
            .map(|s| parse_line(&s))
            .filter_map(|x| x)
            .map(|x| validate_data_part1(&x))
            .filter(|x| *x == true)
            .count();

        println!("Part 1: {}", valid_count);
    }

    if let Ok(lines) = read_lines_str("input.txt") {
        let valid_count: usize = lines
            .into_iter()
            .map(|s| parse_line(&s))
            .filter_map(|x| x)
            .map(|x| validate_data_part2(&x))
            .filter(|x| *x == true)
            .count();

        println!("Part 2: {}", valid_count);
    }
}

#[derive(Clone, Debug)]
struct DBData {
    lb: i32,
    ub: i32,
    letter: char,
    password: String,
}
/*
    Input: "1-2 a: aaccbe"
    Output: { 1, 2, 'a', "aaccbe" }
*/
fn parse_line(line: &String) -> Option<DBData> {
    lazy_static! {
        static ref RE: Regex = Regex::new(r"^(\d+)-(\d+)\s([a-z]):\s([a-z]+)$").unwrap();
    }
    let caps = RE.captures(line).unwrap();

    let lb = caps
        .get(1)
        .map_or(-1, |m| m.as_str().parse::<i32>().unwrap());

    let ub = caps
        .get(2)
        .map_or(-1, |m| m.as_str().parse::<i32>().unwrap());

    let letter = caps
        .get(3)
        .map_or('.', |m| m.as_str().chars().next().unwrap());
    let pass = caps.get(4).map_or("", |m| m.as_str());

    if lb == -1 || ub == -1 || letter == '.' || pass.is_empty() {
        return None;
    }

    return Some(DBData {
        lb: lb,
        ub: ub,
        letter: letter,
        password: pass.to_string(),
    });
}

fn validate_data_part1(data: &DBData) -> bool {
    let l_count = data.password.chars().filter(|x| *x == data.letter).count() as i32;
    return l_count >= data.lb && l_count <= data.ub;
}

fn validate_data_part2(data: &DBData) -> bool {
    if data.lb - 1 >= data.password.len() as i32 || data.ub - 1 >= data.password.len() as i32 {
        return false;
    }

    let lb = data.password.chars().nth(data.lb as usize - 1).unwrap();
    let ub = data.password.chars().nth(data.ub as usize - 1).unwrap();

    if (lb == data.letter) && (ub == data.letter) {
        return false;
    }

    if (lb == data.letter) || (ub == data.letter) {
        return true;
    }

    return false;
}
