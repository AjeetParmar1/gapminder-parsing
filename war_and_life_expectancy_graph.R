library(dslabs)
library(tidyverse)
library(gtools)

data("gapminder")

gapminder %>% filter(country %in% c("China", "Vietnam", "United States",)) %>% 
  ggplot(aes(x = year, y = life_expectancy, color = country)) + geom_line() + 
  ggtitle("Life Expectancy of China, Vietnam, and the US from 1960-2010") + 
  xlab("year") + ylab("life expectancy")