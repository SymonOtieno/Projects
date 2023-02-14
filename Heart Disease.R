#-----------------------------------------------------------------#
                        # HEART DISEASE ANALYSIS #
#-----------------------------------------------------------------#

#-----------------------------------------#
# Step 1: Business Understanding
#-----------------------------------------#
# In this example, the problem is to predict the patient with a heart disease condition.


#-----------------------------------------#
# Step 2: Data Understanding
#-----------------------------------------#
# Install Packages
install.packages("corrplot")
install.packages("caret")

# Load Libraries
library(corrplot)
library(caret)

#Set working directory
setwd("Documents/R/Heart Disease")

# Let's read the CSV file into R and explore the data
# Load the data
data <- read.csv("heart.csv")

# Check the structure of the data
str(data)

# Check the first few records of the data
head(data)

# Select the important variables
important_vars <- c("age", "sex", "cp", "trestbps", "chol", "fbs", "restecg", "thalach", "exang", "oldpeak", "slope", "ca", "thal", "target")
data <- data[, important_vars]

# Plot the correlation matrix

corr <- cor(data)
corrplot(corr, method = "color")

#-----------------------------------------#
# Step 3: Data Preparation
#-----------------------------------------#
# Clean and transform the data as necessary

# Check for missing values
sum(is.na(data))

# Remove any columns with high missing values
data <- data[, colSums(is.na(data)) == 0]

# Check for outliers
boxplot(data)


#-----------------------------------------#
# Step 4: Modeling
#-----------------------------------------#
# Apply statistical or machine learning algorithms to build predictive models

# Split the data into training and test sets
set.seed(123)
split <- createDataPartition(data$target, p = 0.7, list = FALSE)
training_data <- data[split, ]
test_data <- data[-split, ]

# Fit a linear regression model on the training data
model <- lm(target ~ ., data = training_data)

# Summary of the model
summary(model)


#-----------------------------------------#
# Step 5: Evaluation
#-----------------------------------------#
# Predict the model using the test data
predictions <- predict(model, newdata = test_data)

# Calculate the root mean squared error (RMSE)
rmse <- sqrt(mean((data$target - predictions)^2))


# Cross-Validation

# Define the number of folds
k <- 20

# Perform k-fold cross-validation
cv_results <- trainControl(method = "cv", number = k)
logistic_regression_cv <- train(x = training_data[, -1], y = training_data[, 1], method = "glm", trControl = cv_results)

# Print the results
print(logistic_regression_cv)


#-----------------------------------------#
# Step 6: Deployment
#-----------------------------------------#
# Implement the chosen model

# Deploy the linear regression model
deployed_model <- model


#-----------------------------------------#
# Step 7: Monitoring
#-----------------------------------------#

# Regularly monitor the deployed solution to ensure its continued performance

# Check the RMSE of the deployed model on new data
new_data <- read.csv("heart.csv")
new_predictions <- predict(deployed_model, newdata = new_data)
new_rmse <- sqrt(mean((new_data$target - new_predictions)^2))
