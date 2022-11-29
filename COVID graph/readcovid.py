#Oliver Bartz
#ECE 303 
#Assignment 12, part 2
#Due 11/13/2022

import requests
import matplotlib.pyplot as plt
import pandas as pd
import re
import numpy as np

#"constant" value, determines number of x-labels in line graph
trim = 35                   #recommended range 20-80, must be positive int

#get data
url1 = 'https://raw.githubusercontent.com/owid/covid-19-data/master/public/data/latest/owid-covid-latest.csv'
url2 = 'https://raw.githubusercontent.com/nytimes/covid-19-data/master/rolling-averages/us.csv'
world = pd.read_csv(url1)
usa = pd.read_csv(url2)

#delete unused columns
locations = world['location']
cases_world = world['total_cases']
world = pd.concat([locations, cases_world], axis=1)
dates = usa['date']
cases_usa = usa['cases']
usa = pd.concat([dates, cases_usa], axis=1)

#find the income entries and delete them (world data)
toGo = []
a = re.compile('income')
for row in range(0, world.shape[0]):
    if a.search(world.iloc[row,0]):
        toGo.append(row)
world = world.drop(index=toGo)

#sort by cases, trim to top 10 (world data)
world = world.sort_values(by='total_cases', ignore_index=True, ascending=False)
world = world[0:10]

#play with data to prepare for good printout:
world['total_cases'] = world['total_cases'] / 1000000       #change unit to millions
for row in range(0,10):                                     #replace spaces with newlines to avoid text overlap
    world.iloc[row,0] = re.sub('\s', '\n', world.iloc[row,0])

usa['cases'] = usa['cases'] / 1000                          #change unit to thousands

#make better axis labels that won't run together
delete = []
for row in range(0, usa.shape[0]):                          #grab every (trim)th value, removing labels for all others
    if ((row % trim) != 0):
        delete.append(row)
usa_short = usa.drop(delete)                                #store in new dataframe
usa_short = usa_short.reset_index(drop=True)

days = []
months = []
years = []
for row in range(0, usa_short.shape[0]):                    #split up the dates so they can be printed prettier
    temp = str(usa_short.iloc[row,0]).split('-')
    years.append(temp[0])
    months.append(temp[1])
    days.append(temp[2])
usa_short['days'] = days
usa_short['months'] = months
usa_short['years'] = years

labels = []                                                 #print the new labels in desired format to new column
for row in range(0, usa_short.shape[0]):
    labels.append(str(usa_short.iloc[row,3]) + "/" + str(usa_short.iloc[row,4]))
usa_short['labels'] = labels

#display graphs
fig, (sw, sus) = plt.subplots(2, 1, figsize=(12, 8))

sw.bar(world['location'], world['total_cases'])
sw.set_title("Worldwide COVID Cases")
sw.set_xlabel("Location")
sw.set_ylabel("Total Cases (Millions)")

sus.plot(usa['date'], usa['cases'])
sus.set_xticks(ticks=np.arange(0, usa.shape[0], trim), labels=usa_short.iloc[range(0, usa_short.shape[0]),5], rotation=70)
sus.set_title("USA COVID Cases")
sus.set_xlabel("Date")
sus.set_ylabel("Total Cases (Thousands)")

fig.subplots_adjust(hspace=0.4)                             #keep the axis title and graph title from overlapping
plt.show()