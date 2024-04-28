import csv
import random
from sklearn import svm
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split

# Read data from file
with open("dataset.csv") as f:
    reader = csv.reader(f)
    next(reader)  # Skip header
    data = [{
        "evidence": [float(cell) for cell in row[:4]],
        "label": "Authentic" if row[4] == "0" else "Counterfeit"
    } for row in reader]

# Separate features and labels
X = [row["evidence"] for row in data]
y = [row["label"] for row in data]

# Split data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=42)

# Choose and train a model
model = svm.SVC()
model.fit(X_train, y_train)

# Make predictions
predictions = model.predict(X_test)

# Calculate accuracy
accuracy = accuracy_score(y_test, predictions)

# Print results
print(f"Accuracy: {accuracy * 100:.2f}%")
