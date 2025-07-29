# InfectionNetwork-ConsoleApp

This is a simple console application written in C++ that models a network of patients and their infection status. The program reads a list of people, their infection states, and their direct contacts from an input file, then allows interactive exploration of this network.

## Features

- Displays patient names and their infection status (infected or not)
- Shows direct contacts for each patient
- Checks connection between two patients and estimates infection risk
- Provides detailed info about a selected patient’s known infected and healthy contacts
- Identifies connected groups (clusters) of patients using graph traversal (DFS)
- Simple interactive menu with color-coded console output (Windows only)

## How It Works

- Input is read from a file named `date.in` with the following format:
  - Number of patients `n`
  - For each patient: a name and infection status (`true`/`false`)
  - List of pairs representing direct contacts between patients

- The program builds an undirected graph representing the patient network and computes connectivity and groups.

- User navigates the menu with 'w' and 's' keys and selects options with Enter.

## Requirements

- Windows OS (uses Windows console API for colors and input)
- C++ compiler supporting C++11 or later

## Usage

1. Prepare a `date.in` file with the input data.
2. Compile and run the program.
3. Use the menu to explore patient connections and infection status.

## About This Project

This project was created as part of an 11th grade computer science class over a two-week period. It served as a basic introduction to graphs, DFS, and console-based user interfaces.

## Notes

- Infection risk estimates are basic and for demonstration only.
- No dynamic updates or real infection modeling.
