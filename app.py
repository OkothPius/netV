from flask import Flask, render_template
import pandas as pd

app = Flask(__name__)

@app.route("/")
def index():
    # Read the speed test results from the CSV file
    results_df = pd.read_csv("speedtest_results.csv")
    
    # Create a table that displays the results
    table_html = results_df.to_html(index=False)
    
    # Render the template with the table
    return render_template("index.html", table_html=table_html)

if __name__ == "__main__":
    app.run()
