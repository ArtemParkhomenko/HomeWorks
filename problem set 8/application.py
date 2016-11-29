from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *
from myHelpers import *
# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database

@app.route("/")
@login_required
def index():
    
    id = session["user_id"]
    
    cash = getCash(id) # Look in myHelpers

    userShares = parseTransactions(id) # Look in myHelpers
    total = getTotal(cash, userShares) # Look in myHelpers
    
    return render_template("index.html", cash=cash, total=total, output=userShares)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return render_template("buy.html", error = "Need provide symbols")
        if lookup(request.form.get("symbol")) == None:
            return render_template("buy.html", error = "Invalid symbols")
        
        if not request.form.get("shares"):
            return render_template("buy.html", error = "Need provide shares")
        if request.form.get("shares").isalpha() or int(request.form.get("shares")) < 1:
            return render_template("buy.html", error = "Invalid shares")
        
        id = session["user_id"]
        cash = getCash(id) # Look in myHelpers

        symbols = lookup(request.form.get("symbol"))
        name = symbols.get('name')
        price = symbols.get('price')
        symbol = symbols.get('symbol')
        
        shares = int(request.form.get("shares"))
        
        transactions = cash - price * shares
        if transactions < 0:
            return render_template("buy.html", error = "Ohhh, you haven't enough money")
        
        addTransaction(id, symbol, name, shares, price, transactions) # Look in myHelpers 
        
        return render_template("buy.html", success = "This excellent choice.")
    
    else:        
            return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    id = session["user_id"]
    transactions = db.execute('SELECT symbol, name, shares, price, timestamp FROM transactions WHERE user_id = :id', id=id)

    return render_template('history.html', output=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return render_template("login.html", error = "need provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return render_template("login.html", error = "need provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return render_template("login.html", error = "Invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        
        if not request.form.get("symbol"):
            return render_template("quote.html", error = "Need provide symbols")
        if lookup(request.form.get("symbol")) == None:
            return render_template("quote.html", error = "Invalid symbols")
            
        symbol = lookup(request.form.get("symbol"))
        return render_template("quote.html", symbol=symbol)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    if request.method == "POST":
        # ensure username was registration
        if not request.form.get("username"):
            return render_template("register.html", error = "Need provide username")

        # ensure password was registration
        elif not request.form.get("password"):
            return render_template("register.html", error = "Need provide password")
            
        # password check    
        elif not request.form.get("confirmation") == request.form.get("password"):
            return render_template("register.html", error = "Password don't much")
            
        if db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username")):
            return render_template("register.html", error = "This username taken")
        
        # query database for username
        sqlCommand = "INSERT INTO users (username, hash) VALUES(:username, :hash)" 
        db.execute(sqlCommand, username=request.form.get("username"), hash=pwd_context.encrypt(request.form.get("password")))
        
        return render_template("login.html", success = "You create account.")    
    else:
        return render_template("register.html")
        
        
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return render_template("sell.html", error = "Need provide symbols")
        if lookup(request.form.get("symbol")) == None:
            return render_template("sell.html", error = "Invalid symbols")
            
        id = session["user_id"]
        
        if not db.execute("SELECT symbol FROM transactions WHERE symbol = :symbol AND user_id = :id",
                        symbol=request.form.get("symbol").upper(), id = id):
            return render_template("sell.html", error = "You didn't buy this symbol")
        
        if not request.form.get("shares"):
            return render_template("sell.html", error = "Need provide shares")
        if request.form.get("shares").isalpha() or int(request.form.get("shares")) < 1:
            return render_template("sell.html", error = "Invalid shares")
        
        cash = getCash(id) # Look in myHelpers

        symbols = lookup(request.form.get("symbol"))
        name = symbols.get('name')
        price = symbols.get('price')
        symbol = symbols.get('symbol')
        
        shares = int(request.form.get("shares"))
        totalShares = getShares(id, symbol)
        if totalShares - shares < 0:
            return render_template("sell.html", error = "Too many shares")

        transactions = cash + price * shares
        
        addTransaction(id, symbol, name, -shares, price, transactions) # Look in myHelpers 
        
        return render_template("sell.html", success = "This excellent choice.")
    
    else:        
            return render_template("sell.html")
            
@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changepassword():
    """Get stock changepassword."""
    if request.method == "POST":
        if not request.form.get("current-password"):
            return render_template("changepassword.html", error = "Need provide current password")

        # ensure password was registration
        elif not request.form.get("new-password"):
            return render_template("changepassword.html", error = "Need provide new password")
            
        id=session['user_id']
        
        # password check    
        rows = getUser(id)
        if not pwd_context.verify(request.form.get("current-password"), rows[0]["hash"]):
            return render_template("changepassword.html", error = "Invalid current password")
        
        sqlCommand = "UPDATE users SET hash = :hash WHERE id = :id"
        db.execute(sqlCommand, id = id, hash = pwd_context.encrypt(request.form.get("new-password")))
        return render_template("changepassword.html", success = "Passwrod change.")
    else:
        return render_template("changepassword.html")
        
@app.route("/addmoney", methods=["GET", "POST"])
@login_required
def addmoney():
    """Get stock addmoney."""
    if request.method == "POST":
        if not request.form.get("add-money"):
            return render_template("addmoney.html", error = "Need provide money")
        if request.form.get("add-money").isalpha() or request.form.get("secret-key").isalpha():
            return render_template("addmoney.html", error = "Invalid entry")

        # ensure password was registration
        elif not request.form.get("secret-key"):
            return render_template("addmoney.html", error = "Need provide secret-key (0101 0101)‬")
            
        id=session['user_id']
        
        # password check    
        if not int(request.form.get("secret-key")) == 85:
            return render_template("addmoney.html", error = "Invalid secret-key (0101 0101)")
        
        rows = getUser(id)
        cash = rows[0]['cash']
        money = int(request.form.get("add-money"))
        
        sqlCommand = "UPDATE users SET cash = :cash WHERE id = :id"
        db.execute(sqlCommand, id = id, cash = cash+money)
       
        return render_template("addmoney.html", success = "Yeah, baby!")
    else:
        return render_template("addmoney.html")
