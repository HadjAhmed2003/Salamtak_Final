from selenium import webdriver
from selenium.webdriver.common.by import By
import pyodbc
PATH = "C:\Program Files (x86)\chromedriver.exe"
driver = webdriver.Chrome(PATH)
driver.get("https://www.nhsinform.scot/illnesses-and-conditions/a-to-z")
diseases = driver.find_elements_by_class_name("nhs-uk__az-link")
for disease in diseases: 
    print(disease.text)
conn = pyodbc.connect(
    "Driver={SQL Server};"
    "Server=.\SQLEXPRESS;"
    "Database=salamtak;"
    "Trusted_Connection=yes;"
)

cursor = conn.cursor() 
for disease in diseases: 
    print(disease.text)
    cursor.execute("insert into diseases_dataset values(?)", disease.text)
    cursor.commit()
    print('done')
