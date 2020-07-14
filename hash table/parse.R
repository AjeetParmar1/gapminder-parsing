library(dslabs)
library(tidyverse)
library(plyr)

data("gapminder")

gapminder$country <- gsub(' ','',gapminder$country)
gapminder$country <- gsub(',','',gapminder$country)
gapminder$continent <- gsub(' ','',gapminder$continent)
gapminder$region <- gsub(' ','',gapminder$region)
gapminder <- gapminder %>% filter(year %% 10 == 0)
write.csv(gapminder, file = "gapminder.txt", row.names = FALSE)
