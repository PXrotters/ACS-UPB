from flask import Flask, request, render_template, redirect, url_for

# Note: static folder means all files from there will be automatically served over HTTP
app = Flask(__name__, static_folder="public")

# TODO Task 03: you can use a global variable for storing the auth session
# e.g., add the "authenticatedF" (boolean) and "username" (string) keys.
session = {
    "authenticatedF": False,
    "username": None
}

# you can use a dict as user/pass database
ALLOWED_USERS = { "admin": "n0h4x0rz-plz" }

# Task 04: database filename
DATABASE_FILE = "database.txt"

@app.route("/")
def index():
    # TODO Task 02: render the index page using our template
    authenticatedF = session.get("authenticatedF", False)
    username = session.get("username", "")
    return render_template("index.html", authenticatedF=authenticatedF, username=username)

# TODO Task 03: Authentication
@app.route("/login.html")
def login():
    error_msg = ""
    if request.method == "POST":
        username = request.form.get("username", "")
        password = request.form.get("password", "")
        # TODO: Verify credentials and set the session dict
        session["authenticated"] = True
        session["username"] = username
        return redirect(url_for("account_details"))
    return render_template("login.html", error_msg=error_msg)


@app.route("/logout.html")
def logout():
    session["authenticatedF"] = False
    session["username"] = None
    return redirect(url_for("index"))

# You can use this as a starting point for Task 04
# (note: you need a "write" counterpart)
def read_database(filename):
    """ Reads the user account details database file (line by line). """
    with open(filename, "rt") as f:
        line1 = f.readline()
        line2 = f.readline()
        age = int(f.readline())
        return {
            "first_name": line1,
            "last_name": line2,
            "age": age,
        }

# TODO Task 04: Save Account Details
@app.route("/account-details")
def upload():
    if request.method == "POST":
        # Retrieve form data
        first_name = request.form.get("first_name", "")
        last_name = request.form.get("last_name", "")
        age = request.form.get("age", "")

        # Write data to the database file
        with open(DATABASE_FILE, "w") as file:
            file.write(f"First Name: {first_name}\n")
            file.write(f"Last Name: {last_name}\n")
            file.write(f"Age: {age}\n")

        # Redirect back to the account details page
        return redirect("/account-details")
    else:
        # Read data from the database file
        data = {}
        with open(DATABASE_FILE, "r") as file:
            for line in file:
                key, value = line.strip().split(":")
                data[key.strip()] = value.strip()

        # Render the account details template and pass the data
        return render_template("account-details.html", data=data)
    
# Run the webserver (port 5000 - the default Flask port)
if __name__ == "__main__":
    app.run(debug=True, port=5000)

