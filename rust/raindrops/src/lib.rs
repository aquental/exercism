pub fn raindrops(n: usize) -> String {
    let pling = "Pling";
    let plang = "Plang";
    let plong = "Plong";
    let mut res = String::new();
    if n % 3 == 0 {
        res.push_str(pling);
    }
    if n % 5 == 0 {
        res.push_str(plang);
    }
    if n % 7 == 0 {
        res.push_str(plong);
    }
    if res == "" {
        format!("{}", n)
    } else {
        res
    }
}
