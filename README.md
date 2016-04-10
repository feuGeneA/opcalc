Yet another option calculator
=============================

A web application for calculating values of American one-asset option contracts

Uses Wt (webtoolkit.eu) to implement the web interface, and QuantLib (quantlib.org) to do the calculations.  Uses Wt's WFormModel/WTemplateFormView MVC paradigm to ensure that all calculations are performed on the server side rather than being pushed by Wt to the client side.  Via QuantLib, supports several different analysis engines and stochastic processes.
