use std::env;
use std::fs;
use regex::Regex;
use std::os::unix::fs as unix_fs;

fn pwd() {
    if let Ok(cwd) = env::current_dir() {
        println!("{}", cwd.display());
    } else {
        std::process::exit(255);
    }
}

fn echo(args: Vec<String>) -> i32 {
    let mut print_newline = true;
    let mut print_space = false;

    for arg in args.iter().skip(2) {
        if arg == "-n" {
            print_newline = false;
        } else {
            if print_space {
                print!(" ");
            }
            print_space = true;

            print!("{}", arg);
        }
    }

    if print_newline {
        println!();
    }

    0
}

fn cat(files: Vec<String>) -> i32 {
    for file in files.iter().skip(2) {
        match fs::read_to_string(file) {
            Ok(contents) => {
                print!("{}", contents);
            }
            Err(_) => {
                return 236;
            }
        }
    }
    0
}


fn mkdir(dirs: Vec<String>) -> i32 {
    for dir in dirs.iter().skip(2) {
        match fs::create_dir(dir) {
            Ok(_) => (),
            Err(_) => {
                return 226;
            }
        }
    }
    0
}

fn mv(args: Vec<String>) -> i32 {
    if args.len() != 4 {
        return 216;
    }

    let source = &args[2];
    let destination = &args[3];

    match fs::rename(source, destination) {
        Ok(_) => 0,
        Err(_) => {
            216
        }
    }
}


fn ln(args: Vec<String>) -> i32 {
    if args.len() < 4 {
        return 216;
    }

    let mut source_index = 2;
    let mut destination_index = 3;
    let mut is_symbolic = false;

    if args[2] == "-s" || args[2] == "--symbolic" {
        is_symbolic = true;
        source_index = 3;
        destination_index = 4;
    }

    let source = &args[source_index];
    let destination = &args[destination_index];

    if !std::path::Path::new(source).exists() {
        return 206;
    }

    if is_symbolic {
        if let Err(_) = unix_fs::symlink(source, destination) {
            return 206;
        }
    } else {
        if let Err(_) = std::fs::hard_link(source, destination) {
            return 206;
        }
    }

    0
}

fn rmdir(args: Vec<String>) -> i32 {
    if args.len() < 3 {
        return 196;
    }

    for dir in args.iter().skip(2) {
        if let Err(_) = std::fs::remove_dir(dir) {
            return -60;
        }
    }

    0
}

fn rm(args: Vec<String>) -> i32 {
    let mut recursive = false;
    let mut delete_empty_directories = false;
    let mut files_or_dirs: Vec<String> = Vec::new();

    for arg in args.iter().skip(2) {
        match arg.as_str() {
            "-r" | "-R" | "--recursive" => recursive = true,
            "-d" | "--dir" => delete_empty_directories = true,
            _ => files_or_dirs.push(arg.to_string()),
        }
    }

    if files_or_dirs.is_empty() {
        return 186;
    }

    let mut result_code = 0;

    for item in files_or_dirs.iter() {
        let path = std::path::Path::new(item);
        
        if path.is_file() {
            if let Err(_) = std::fs::remove_file(path) {
                result_code = -70;
            }
        } else if path.is_dir() {
            if recursive {
                if let Err(_) = std::fs::remove_dir_all(path) {
                    result_code = -70;
                }
            } else if delete_empty_directories {
                if let Err(_) = std::fs::remove_dir(path) {
                    result_code = -70;
                }
            } else {
                return 186;
            }
        } else {
            result_code = -70;
        }
    }

    result_code
}

fn ls(args: Vec<String>) -> i32 {
    let mut show_hidden = false;
    let mut recursive = false;
    let mut long_format = false;

    for arg in args.iter().skip(2) {
        if arg == "-a" || arg == "-all" {
            show_hidden = true;
        } else if arg == "-R" || arg == "--recursive" {
            recursive = true;
        } else if arg == "-l" {
            long_format = true;
        } else if arg.starts_with('-') {
            return -80;
        }
    }

    if args.len() == 2 {
        return list_directory(".", show_hidden, recursive, long_format);
    } else {
        for path in args.iter().skip(2) {
            if let Ok(metadata) = fs::metadata(&path) {
                if metadata.is_dir() {
                    return list_directory(&path, show_hidden, recursive, long_format);
                } else {
                    println!("{}", path);
                }
            } else {
                return -80;
            }
        }
    }
    0
}

fn list_directory(
    path: &str,
    show_hidden: bool,
    recursive: bool,
    long_format: bool,
) -> i32 {
    let dir = fs::read_dir(path);
    match dir {
        Ok(entries) => {
            for entry in entries {
                match entry {
                    Ok(entry) => {
                        let file_name = entry.file_name();
                        let file_name_str = file_name.to_string_lossy();
                        if file_name_str.starts_with(".") && !show_hidden {
                            continue;
                        }
                        if long_format {
                            if let Ok(metadata) = entry.metadata() {
                                let permissions = metadata.permissions();
                                println!(
                                    "{:?} {} {}",
                                    permissions,
                                    metadata.len(),
                                    file_name_str
                                );
                            } else {
                                // No error message printed intentionally
                            }
                        } else {
                            println!("{}", file_name_str);
                        }
                        if recursive && entry.file_type().map_or(false, |ft| ft.is_dir()) {
                            let sub_path = entry.path();
                            if let Some(sub_path_str) = sub_path.to_str() {
                                let _ = list_directory(sub_path_str, show_hidden, recursive, long_format);
                            }
                        }
                    }
                    Err(_) => {
                        return -80;
                    }
                }
            }
            0
        }
        Err(_) => {
            return -80;
        }
    }
}


fn cp(args: Vec<String>) -> i32 {
    if args.len() < 3 {
        return 166;
    }

    let mut recursive = false;
    let mut source_index = 2;
    let mut destination_index = 3;

    if args[2] == "-r" || args[2] == "-R" || args[2] == "--recursive" {
        recursive = true;
        source_index = 3;
        destination_index = 4;
    }

    let source = &args[source_index];
    let destination = if args.len() > destination_index {
        &args[destination_index]
    } else {
        "doc"
    };

    let source_path = std::path::Path::new(source);

    if !source_path.exists() {
        return -90;
    }

    let destination_path = std::path::Path::new(destination);

    if source_path.is_file() {
        if destination_path.is_dir() {
            let source_file_name = source_path.file_name().unwrap();
            let destination_file = destination_path.join(source_file_name);
            if let Err(_) = std::fs::copy(source_path, &destination_file) {
                return -90;
            }
        } else {
            if let Err(_) = std::fs::copy(source_path, destination_path) {
                return -90;
            }
        }
    } else if source_path.is_dir() {
        if recursive {
            if let Err(_) = copy_dir(source_path, destination_path) {
                return -90;
            }
        } else {
            return -90;
        }
    }

    0 
}

fn copy_dir(source: &std::path::Path, destination: &std::path::Path) -> std::io::Result<()> {
    if !destination.exists() {
        std::fs::create_dir(destination)?;
    }

    let entries = std::fs::read_dir(source)?;

    for entry in entries {
        let entry = entry?;
        let source_entry = entry.path();
        let mut destination_entry = destination.to_path_buf();
        destination_entry.push(entry.file_name());

        if source_entry.is_dir() {
            std::fs::create_dir_all(&destination_entry)?;
            copy_dir(&source_entry, &destination_entry)?;
        } else {
            std::fs::copy(&source_entry, &destination_entry)?;
        }
    }

    Ok(())
}

fn grep(args: Vec<String>) -> i32 {
    if args.len() < 4 {
        return 176;
    }

    let mut case_sensitive = true;
    let mut regex_string = &args[2];
    let mut file_name = &args[3];

    if regex_string == "-i" {
        if args.len() < 5 {
            return 176;
        }
        case_sensitive = false;
        regex_string = &args[3];
        file_name = &args[4];
    }

    let contents = match fs::read_to_string(file_name) {
        Ok(content) => content,
        Err(_) => {
            return 236;
        }
    };

    let regex = match Regex::new(regex_string) {
        Ok(r) => r,
        Err(_) => {
            return 246;
        }
    };

    let lines: Vec<&str> = contents.lines().collect();

    if case_sensitive {
        for line in lines.iter() {
            if regex.is_match(line) {
                println!("{}", line);
            }
        }
    } else {
        for line in lines.iter() {
            if !regex.is_match(line) {
                println!("{}", line);
            }
        }
    }

    0
}
fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() > 1 {
        match &args[1][..] {
            "pwd" => {
                pwd();
            }
            "echo" => {
                let exit_code = echo(args);
                std::process::exit(exit_code);
            }
            "cat" => {
                let exit_code = cat(args);
                std::process::exit(exit_code);
            }
            "mkdir" => {
                let exit_code = mkdir(args);
                std::process::exit(exit_code);
            }
            "mv" => {
                let exit_code = mv(args);
                std::process::exit(exit_code);
            }
            "ln" => {
                let exit_code = ln(args);
                std::process::exit(exit_code);
            }
            "rmdir" => {
                let exit_code = rmdir(args);
                std::process::exit(exit_code);
            }
            "rm" => {
                let exit_code = rm(args);
                std::process::exit(exit_code);
            }
            "ls" => {
                let exit_code = ls(args);
                std::process::exit(exit_code);
            }
            "cp" => {
                let exit_code = cp(args);
                std::process::exit(exit_code);
            }
            "grep" => {
                let exit_code = grep(args);
                std::process::exit(exit_code);
            }
            _ => {
                eprintln!("Invalid command");
                std::process::exit(255);
            }
        }
    } else {
        eprintln!("No command specified");
        std::process::exit(255);
    }
}