# order-book
A stock trading (order matching) system utilizing an order book written in C++.
## Description 
The simulated orders stream should be in a .dat/.txt file with 4 kinds of orders.
Each order has the format:
Order type, action, price, shares, account ID, separated by a space. The code for order type is 0:
market order, 1: limited order. The code for action is 1: buy (bid), -1: sell (ask). For market order, the
price is 0, otherwise, price is a number with 2 decimal places. For example,
1. Market buy (bid) order: 0 1 0 100 999887777
2. Market sell (ask) order: 0 -1 0 200 888776666
3. Limited buy (bid) order: 1 1 114.53 100 777665555
4. Limited sell (ask) order: 1 -1 114.54 200 666554444
## How It Works
The program uses a queue to store limited orders of bids (buys) and asks (sells) while it
process the transactions and records them in an audit (transaction) file as follows:

*Buyer ID, Seller ID, Price, Shares, Time Stamp.*

A transaction record would be as follows:

999887777 666554444 114.54 100 1415959388
## Results
Upon running the program, the following occurs:
1. Two files are produced, a bidbook and a askbook to store the unmatched limited orders of bid and ask at the end of the process, respectively.
2. Terminal shows the following:

![stocks](https://user-images.githubusercontent.com/53231599/61754721-54b4ce80-ad82-11e9-8a4f-eff35ca0c191.PNG)


## Credits
This project could not have possible without my team member Jessie Han. Thank you for your patience and dedication. 

