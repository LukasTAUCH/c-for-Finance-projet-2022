## c-for-Finance-projet-2022

The purpose of this code is to determine the **initial price** of an option (**European, Asian, American**) following 2 methods either the **BlackSholes or the CRRP**.

## EUROPEAN Option :

# **Abstract class** Option 

- with a private member double _expiry, along with a getter method getExpiry()
- with a pure virtual method double payoff(double), payoff() represents the function h
- write a constructor that initialize _expiry with an argument

# Derive Option into **Abstract class Vanilla Option**

- with private attributes double _strike
- write a constructor which initialize _expiry and _strike with arguments (call the base
constructor)
- the constructor should ensure that the arguments are nonnegative
- write a classe enum optionType that has two values: call and put
- write an pure virtual method GetOptionType() which should return an optionType enum

# Derive VanillaOption into 2 classes : **CallOption and PutOption**

They should use the constructor of VanillaOption
- For a Call option with strike K, the payoff is given by **h(z) = z − K if z ≥ K**
 0 otherwise.
- For a Put option with strike K, the payoff is given by **h(z) = K − z if K ≥ z**
0 otherwise.
- Override the GetOptionType() accordingly in the derived classes

# Class BlackScholesPricer

- With constructor BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility)
- Declare BlackScholesPricer as a friend class of VanillaOption in order for the former
to access the strike of the latter
- Write the operator() which returns the price of the option
- Write the method delta() which returns the Delta of the option

# Class BinaryTree for CRR method 
- It should be a template class BinaryTree<T>
- It should have a member _depth, representing N
- It should contain a private member _tree, a vector of vectors (STL) to hold data of
type T
- Implement the setter method setDepth(int) a setter for _depth, that resizes _tree and
allocate/deallocate properly the vectors in tree
- Implement the setter method setNode(int, int, T) which sets the value stored in _tree
at the given indices
- Implement the getter method getNode(int, int) which retrives the corresponding value
- Implement the method display() which prints the all the values stored
  
# Class CRRPricer 
- With constructor CRRPricer(Option* option, int depth, double asset_price, double up,
double down, double interest_rate) :
   - depth: N
   - asset_price: S0
   - up, down, interest_rate: U, D, R respectively
- In the constructor, check for arbitrage
- Create the tree structure to store the tree of the desired depth (hint: use BinaryTree
with an appropriate type)
- Write the method void compute() that implements the CRR procedure
- Write the getter method get(int, int) that returns H (n, i).
- Write the operator() which returns the price of the option, it must call compute() if
needed
- The CRR method provides also a closed-form formula for option pricing:
  **H(0, 0) = (1 / (1 + R)^N) Sum_i=0 to N { ( N! / (i!(N - i)!)) q^i (1-q)^(N-i) h(S(N,i)) }**
  
Put an optional argument bool closed_form that defaults to false to the operator().
When it is set to true, the above formula should be used instead of the CRR procedure.
  
# DigitalOption Derive classes ( DigitalCallOption and DigitalPutOption)
- Digital Call with payoff: **h(z) = 1z≥K**
- Digital Put with payoff: **h(z) = 1z≤K**
- Enable BlackScholesPricer to price digital options as well (closed form formulas also exist for Black-Scholes prices and deltas for digital options)
  
## ASIAN OPTION :
- Augment the Option class with payoff Path method, taking a std::vector<double> as argument, returning h(St1
, · · · , Stm).
- The non-overriden version of this function should return h (Stm) (calling payoff(double))
 
# Derived class from Option : AsianOption 
- The constructor takes a std::vector<double> as argument, representing (t1, · · · , tm)
- The argument should be stored in a private member, with a getter method getTimeSteps()
- Override AsianOption::payoffPath(std::vector<double>) so that :
  **h(St1, · · · , Stm) = h(1/m sum_k=1 to m { S_tk })**
where h on the right hand side is payoff(double). AsianOption::payoffPath(std::vector<double>)
should not be virtual
  
# Created AsianCallOption and AsianPutOption, derived from AsianOption :  
- In addition to std::vector<double>, their constructor takes a double as argument, defining the strike.
- They have to have proper implementations of payoff().

# Augment the Option class with bool isAsianOption(), returning false in its non-overriden version, override it in AsianOption :

# In CRRPricer 's constructor, check if the option is an Asian option, if it is the case, throw an exception

# Class MT
Design a singleton class MT, encapsulating a std::mt19937 object. Two public static methods
are implemented: double rand_unif() and double rand_norm(), returning a realization of
U ([0, 1]) and N (0, 1) respectively. Ensure that only one instance of std::mt19937 can be
used in all the program through MT
  
# BlackScholesMCPricer class :  
- The constructor must have signature (Option* option, double initial_price, double interest_rate, double volatility)
- The class should have a private attribute that counts the number of paths already
generated since the beginning of the program to estimate the price of the option,
a getter named getNbPaths() needs to give a read access to this attribute.
- The method generate(int nb_paths) generates nb_paths new paths of (St1, · · · , Stm)
(for European Option, m = 1), and UPDATES the current estimate of the price of
the option (the updating process is the same as in TD2).
- The operator () returns the current estimate (throw an exception if it is undefined).
- The method confidenceInterval() returns the 95% CI of the price, as a std::vector<double>
containing the lower bound and the upper bound.
- The random generation have to be handled by calling MT::rand_norm().
- No path should be stored in the object
- Check the prices given by BlackScholesMCPricer are in line with those given by BlackScholesPricer on vanilla options.

 ## AMERICAN OPTION BINOMIAL MODEL 
  
- Augment the Option class with bool isAmericanOption() which returns false in its nonoverriden version
- Derive Option into AmericanOption, and override isAmericanOption() properly
- Derive AmericanOption into AmericanCallOption and AmericanPutOption, write proper
constructors and override their respective payoff() methods
- Modify CRRPricer in order for it to price properly American options; the exercise condition
for American options is stored in a BinaryTree<bool>, accessible through a getter method
bool getExercise(int, int).
The exercise condition is true when the intrinsic value is larger or equal to the continuous
value, it is computed during the CRR procedure.
- Overload the CRRPricer with CRRPricer(Option* option, int depth, double asset_price,
double r, double volatility), which initializes U, D and R as described in Section 2.
  
Set parameters of the binomial model :
  U = e^{(r+ sigma^2/2)h + sigma * sqrt(h)} - 1
  D = e^{(r+ sigma^2/2)h - sigma * sqrt(h)} - 1
  R = e^{rh} - 1
  
  Time interval [0,T] into N steps of length h = T/N
  
Price H(n,i) of an American option :
  
  H(n,i) = max{ (qH(n+1,i+1) + (1-q)H(n+1,i) ) / (1 + R), h(S(n,i)) } 
  
  with (qH(n+1,i+1) + (1-q)H(n+1,i) ) / (1 + R) -> continuation value 
   h(S(n,i)) -> intrinsic value
  
 ## Source code
  The main to test everything 
  
  
  
  
  
  
  
  
  
  
  
  
