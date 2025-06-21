# Data Structure Assignment
# 🙌 Hi everyone, here is our Git repository for Data Structure Assignment
# ⚠️⚠️⚠️ Important: Do not push the dataset into git, else might get banned as the dataset is too HUGE!!!

## 📂 Project Structure
```
DSTR_Assignment/
│
├── cmake-build-debug/                                             # Build folder (auto-generated)
├── src/                                                           # Source code
│ ├── entities/
│ │ └── Transaction.h                                              # Transaction struct definition
│ ├── resources/
│ │ └── financial_fraud_detection_dataset.csv                      # Your Dataset should be here.
│ └── main.cpp                                                     # Main program logic
├── .gitignore
├── CMakeLists.txt
├── README.md
```

## 🧹 How to Build & Run

1. Open the project in CLion
2. Place your dataset in `src/resources/`
3. Run `main.cpp`

Make sure your dataset location matches with the relative path in your code:
```cpp
readCSVToArray("../src/resources/financial_fraud_detection_dataset.csv", totalRows);
```
