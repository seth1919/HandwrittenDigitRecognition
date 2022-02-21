# HandwrittenDigitRecognition
This is a machine learning application which can learn to recognize handwritten numbers from 0 to 9.


To use this program follow these steps:
1. Download the training data. You can find it in the file named NumbersData
2. Run the program.
3. Click File -> New
4. Type the number you want to add in the text box in upper left. (The first time, you want to type "0")
5. Press "Add Category" and choose the folder containing images of the number.
6. Repeat steps 4 and 5 until you have added all the categories for all the training data. (For the numbers 0 to 9, you will have 10 categories)
7. Press "Load Data".
8. Press "Train for 30 epochs". This should take about 8 minutes.
10. Press "Evaluate Accuracy". If the result is anything less than 0.90, something has gone wrong.
11. Test the model by drawing a number in the black canvas and press "Recognize Image".

Currently, this application only works for training a model with 10 categories.
