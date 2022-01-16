# -*- coding: utf-8 -*-
# Problem Set 5: Experimental Analysis
# Name: 
# Collaborators (discussion):
# Time:

import pylab
import re

# cities in our weather data
CITIES = [
    'BOSTON',
    'SEATTLE',
    'SAN DIEGO',
    'PHILADELPHIA',
    'PHOENIX',
    'LAS VEGAS',
    'CHARLOTTE',
    'DALLAS',
    'BALTIMORE',
    'SAN JUAN',
    'LOS ANGELES',
    'MIAMI',
    'NEW ORLEANS',
    'ALBUQUERQUE',
    'PORTLAND',
    'SAN FRANCISCO',
    'TAMPA',
    'NEW YORK',
    'DETROIT',
    'ST LOUIS',
    'CHICAGO'
]

TRAINING_INTERVAL = range(1961, 2010)
TESTING_INTERVAL = range(2010, 2016)

"""
Begin helper code
"""
class Climate(object):
    """
    The collection of temperature records loaded from given csv file
    """
    def __init__(self, filename):
        """
        Initialize a Climate instance, which stores the temperature records
        loaded from a given csv file specified by filename.

        Args:
            filename: name of the csv file (str)
        """
        self.rawdata = {}

        f = open(filename, 'r')
        header = f.readline().strip().split(',')
        for line in f:
            items = line.strip().split(',')

            date = re.match('(\d\d\d\d)(\d\d)(\d\d)', items[header.index('DATE')])
            year = int(date.group(1))
            month = int(date.group(2))
            day = int(date.group(3))

            city = items[header.index('CITY')]
            temperature = float(items[header.index('TEMP')])
            if city not in self.rawdata:
                self.rawdata[city] = {}
            if year not in self.rawdata[city]:
                self.rawdata[city][year] = {}
            if month not in self.rawdata[city][year]:
                self.rawdata[city][year][month] = {}
            self.rawdata[city][year][month][day] = temperature
            
        f.close()

    def get_yearly_temp(self, city, year):
        """
        Get the daily temperatures for the given year and city.

        Args:
            city: city name (str)
            year: the year to get the data for (int)

        Returns:
            a 1-d pylab array of daily temperatures for the specified year and
            city
        """
        temperatures = []
        assert city in self.rawdata, "provided city is not available"
        assert year in self.rawdata[city], "provided year is not available"
        for month in range(1, 13):
            for day in range(1, 32):
                if day in self.rawdata[city][year][month]:
                    temperatures.append(self.rawdata[city][year][month][day])
        return pylab.array(temperatures)

    def get_daily_temp(self, city, month, day, year):
        """
        Get the daily temperature for the given city and time (year + date).

        Args:
            city: city name (str)
            month: the month to get the data for (int, where January = 1,
                December = 12)
            day: the day to get the data for (int, where 1st day of month = 1)
            year: the year to get the data for (int)

        Returns:
            a float of the daily temperature for the specified time (year +
            date) and city
        """
        assert city in self.rawdata, "provided city is not available"
        assert year in self.rawdata[city], "provided year is not available"
        assert month in self.rawdata[city][year], "provided month is not available"
        assert day in self.rawdata[city][year][month], "provided day is not available"
        return self.rawdata[city][year][month][day]

def se_over_slope(x, y, estimated, model):
    """
    For a linear regression model, calculate the ratio of the standard error of
    this fitted curve's slope to the slope. The larger the absolute value of
    this ratio is, the more likely we have the upward/downward trend in this
    fitted curve by chance.
    
    Args:
        x: an 1-d pylab array with length N, representing the x-coordinates of
            the N sample points
        y: an 1-d pylab array with length N, representing the y-coordinates of
            the N sample points
        estimated: an 1-d pylab array of values estimated by a linear
            regression model
        model: a pylab array storing the coefficients of a linear regression
            model

    Returns:
        a float for the ratio of standard error of slope to slope
    """
    assert len(y) == len(estimated)
    assert len(x) == len(estimated)
    EE = ((estimated - y)**2).sum()
    var_x = ((x - x.mean())**2).sum()
    SE = pylab.sqrt(EE/(len(x)-2)/var_x)
    return SE/model[0]

"""
End helper code
"""

def generate_models(x, y, degs):
    """
    Generate regression models by fitting a polynomial for each degree in degs
    to points (x, y).

    Args:
        x: an 1-d pylab array with length N, representing the x-coordinates of
            the N sample points
        y: an 1-d pylab array with length N, representing the y-coordinates of
            the N sample points
        degs: a list of degrees of the fitting polynomial

    Returns:
        a list of pylab arrays, where each array is a 1-d array of coefficients
        that minimizes the squared error of the fitting polynomial
    """
    return [pylab.polyfit(x, y, deg) for deg in degs]


def r_squared(y, estimated):
    """
    Calculate the R-squared error term.
    
    Args:
        y: 1-d pylab array with length N, representing the y-coordinates of the
            N sample points
        estimated: an 1-d pylab array of values estimated by the regression
            model

    Returns:
        a float for the R-squared error term
    """
    return 1 - ((y - estimated)**2).sum()/((y - y.mean())**2).sum()

def evaluate_models_on_training(x, y, models):
    """
    For each regression model, compute the R-squared value for this model with the
    standard error over slope of a linear regression line (only if the model is
    linear), and plot the data along with the best fit curve.

    For the plots, you should plot data points (x,y) as blue dots and your best
    fit curve (aka model) as a red solid line. You should also label the axes
    of this figure appropriately and have a title reporting the following
    information:
        degree of your regression model,
        R-square of your model evaluated on the given data points,
        and SE/slope (if degree of this model is 1 -- see se_over_slope). 

    Args:
        x: an 1-d pylab array with length N, representing the x-coordinates of
            the N sample points
        y: an 1-d pylab array with length N, representing the y-coordinates of
            the N sample points
        models: a list containing the regression models you want to apply to
            your data. Each model is a pylab array storing the coefficients of
            a polynomial.

    Returns:
        None
    """
    for model in models:
        estimated = pylab.polyval(model, x)
        r2 = r_squared(y, estimated)
        pylab.plot(x,y,'bo',label='Measured points')
        pylab.plot(x, estimated, 'r', label = 'fit with degree = %d'%(len(model) - 1))
        pylab.legend(loc = 'best')
        if len(model) == 2:
            se_ratio = se_over_slope(x, y, estimated, model)
            pylab.title('degree = %d, R2 = %.2f, SE/slope = %.2f'%(len(model) - 1, r2, se_ratio))
        else:
            pylab.title('degree = %d, R2 = %.2f'%(len(model) - 1, r2))
        pylab.show()


def gen_cities_avg(climate, multi_cities, years):
    """
    Compute the average annual temperature over multiple cities.

    Args:
        climate: instance of Climate
        multi_cities: the names of cities we want to average over (list of str)
        years: the range of years of the yearly averaged temperature (list of
            int)

    Returns:
        a pylab 1-d array of floats with length = len(years). Each element in
        this array corresponds to the average annual temperature over the given
        cities for a given year.
    """
    return pylab.array([pylab.array([climate.get_yearly_temp(city, year) for city in multi_cities]).mean() for year in years])

def moving_average(y, window_length):
    """
    Compute the moving average of y with specified window length.

    Args:
        y: an 1-d pylab array with length N, representing the y-coordinates of
            the N sample points
        window_length: an integer indicating the window length for computing
            moving average

    Returns:
        an 1-d pylab array with the same length as y storing moving average of
        y-coordinates of the N sample points
    """
    y = pylab.array(y)
    result = [0] * len(y)
    i, j = 0, 0
    while j < len(y):
        result[j] = y[i:j+1].mean()
        if j >= window_length - 1:
            i+=1
        j+=1
    return pylab.array(result)


def rmse(y, estimated):
    """
    Calculate the root mean square error term.

    Args:
        y: an 1-d pylab array with length N, representing the y-coordinates of
            the N sample points
        estimated: an 1-d pylab array of values estimated by the regression
            model

    Returns:
        a float for the root mean square error term
    """
    return pylab.sqrt(((y-estimated)**2).mean())

def gen_std_devs(climate, multi_cities, years):
    """
    For each year in years, compute the standard deviation over the averaged yearly
    temperatures for each city in multi_cities. 

    Args:
        climate: instance of Climate
        multi_cities: the names of cities we want to use in our std dev calculation (list of str)
        years: the range of years to calculate standard deviation for (list of int)

    Returns:
        a pylab 1-d array of floats with length = len(years). Each element in
        this array corresponds to the standard deviation of the average annual 
        city temperatures for the given cities in a given year.
    """
    # TODO
    return pylab.array([pylab.array([climate.get_yearly_temp(city, year) for city in multi_cities]).mean(axis = 0).std() for year in years])


def evaluate_models_on_testing(x, y, models):
    """
    For each regression model, compute the RMSE for this model and plot the
    test data along with the model’s estimation.

    For the plots, you should plot data points (x,y) as blue dots and your best
    fit curve (aka model) as a red solid line. You should also label the axes
    of this figure appropriately and have a title reporting the following
    information:
        degree of your regression model,
        RMSE of your model evaluated on the given data points. 

    Args:
        x: an 1-d pylab array with length N, representing the x-coordinates of
            the N sample points
        y: an 1-d pylab array with length N, representing the y-coordinates of
            the N sample points
        models: a list containing the regression models you want to apply to
            your data. Each model is a pylab array storing the coefficients of
            a polynomial.

    Returns:
        None
    """
    # TODO
    for model in models:
        estimated = pylab.polyval(model, x)
        test_rmse = rmse(y, estimated)
        pylab.plot(x,y,'bo',label='Measured points')
        pylab.plot(x, estimated, 'r', label = 'fit with degree = %d'%(len(model) - 1))
        pylab.legend(loc = 'best')
        pylab.title('degree = %d, RMSE = %.2f'%(len(model) - 1, test_rmse))
        pylab.show()

if __name__ == '__main__':

    pass 

    # Part A.4
    # Part A.4.I
    climate = Climate('data.csv')
    training = pylab.array([climate.get_daily_temp('NEW YORK', 1, 10, year) for year in TRAINING_INTERVAL])
    model = generate_models(pylab.array(TRAINING_INTERVAL), training, [1])
    evaluate_models_on_training(pylab.array(TRAINING_INTERVAL), training, model)
    # Part A.4.II
    training = pylab.array([climate.get_yearly_temp('NEW YORK', year).mean() for year in TRAINING_INTERVAL])
    model = generate_models(pylab.array(TRAINING_INTERVAL), training, [1])
    evaluate_models_on_training(pylab.array(TRAINING_INTERVAL), training, model)
    # Part B
    # TODO: replace this line with your code
    yearly_temp = gen_cities_avg(climate, CITIES, TRAINING_INTERVAL)
    model = generate_models(pylab.array(TRAINING_INTERVAL), yearly_temp, [1])
    evaluate_models_on_training(pylab.array(TRAINING_INTERVAL), yearly_temp, model)

    # Part C
    # TODO: replace this line with your code
    ma = moving_average(yearly_temp, 5)
    model = generate_models(pylab.array(TRAINING_INTERVAL), ma, [1])
    evaluate_models_on_training(pylab.array(TRAINING_INTERVAL), ma, model)

    # Part D.2
    # TODO: replace this line with your code
    # Part D.2.I
    models = generate_models(pylab.array(TRAINING_INTERVAL), ma, [1,2,20])
    evaluate_models_on_training(pylab.array(TRAINING_INTERVAL), ma, models)
    # Part D.2.II
    ma_test = moving_average(gen_cities_avg(climate, CITIES, TESTING_INTERVAL),5)
    evaluate_models_on_testing(pylab.array(TESTING_INTERVAL), ma_test, models)
    # Part E
    # TODO: replace this line with your code
    std_training = gen_std_devs(climate, CITIES, TRAINING_INTERVAL)
    std_ma_training = moving_average(std_training,5)
    model = generate_models(pylab.array(TRAINING_INTERVAL), std_ma_training, [1])
    evaluate_models_on_training(pylab.array(TRAINING_INTERVAL), std_ma_training, model)

