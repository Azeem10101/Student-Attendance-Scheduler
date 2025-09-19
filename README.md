# Student-Attendance-Scheduler
This is a project done in my first year for a Hackathon.

📅 Student Attendance Scheduler:

Built during my first hackathon in 1st year, this project is a smart scheduler that helps students and faculty manage weekly timetables with ease.

🌍 Problem:

Managing college schedules manually is messy — overlapping classes, double-booked faculty, and last-minute changes lead to confusion. Students struggle to keep track, and faculty face scheduling conflicts.

💡 Solution:

The Student Attendance Scheduler is a console-based application written in C that:
1. Creates & manages weekly timetables

2. Detects conflicts (no double-booking or overlaps)

3. Lets you edit & delete sessions

4. Saves schedules automatically to schedule.txt

5. Can auto-generate a weekly timetable for faster setup

6. Uses colored console UI for readability

✨ Features:
1. Add new sessions (subject, faculty, day, time)

2. Conflict detection (time clashes & same faculty checks)

3. Edit or delete existing sessions

4. Auto-generate full week schedule

5. File handling (save/load from disk)

6. Interactive CLI with colored output

🖥️ Tech Stack:
1. Language: C

2. Concepts: Structs, File I/O, String Handling, Conflict Detection, Menu-driven CLI

🌟 Future Enhancements:

1. GUI version (maybe with C++/Qt or Python)

2. Attendance tracking linked to schedule

3. Export as PDF/CSV automatically

4. Cloud sync for multiple users

📂 Project Structure:
📦 Student-Attendance-Scheduler
 ┣ 📜 Best 1.c        # Source code (main program)
 ┣ 📜 schedule.txt    # Sample schedule file (used by the program)
 ┗ 📜 README.md       # Project documentation

🚀 How to Run:
1. Clone this repo:
git clone https://github.com/Azeem10101/Student-Attendance-Scheduler.git
cd Student-Attendance-Scheduler

2. Compile the source:
gcc "Best 1.c" -o scheduler

3. Run:
./scheduler

🏆 About:
This was my first hackathon project in college.
It gave me hands-on experience in C programming, file handling, and building real-world utilities.

