pub mod aoc {
    use std::collections::HashMap;
    use std::fs::File;
    use std::io::{self, BufRead};
    use std::path::Path;
    pub fn find_pair(list: &Vec<i32>, sum: &i32) -> Option<(i32, i32)> {
        let mut diff = HashMap::<i32, i32>::new();
        for num in list.iter() {
            if let Some(_) = diff.get(num) {
                return Some((num.clone(), sum - num));
            }
            diff.insert(sum - num, 1);
        }
        return None;
    }
    pub fn read_lines_str<P>(filename: P) -> io::Result<Vec<String>>
    where
        P: AsRef<Path>,
    {
        let file = File::open(filename)?;
        Ok(io::BufReader::new(file)
            .lines()
            .collect::<Result<_, _>>()
            .unwrap())
    }
}
