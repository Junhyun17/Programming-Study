#!/bin/bash

current_rate=$(curl -s "https://api.frankfurter.dev/v1/latest?base=USD&symbols=KRW" | jq '.rates.KRW')

week_avg=$(curl -s "https://api.frankfurter.dev/v1/2026-05-20..2026-05-26?base=USD&symbols=KRW" | jq '[.rates[].KRW] | add / length')

echo "=============================="
echo " 환율 기반 소비 판단 시스템"
echo "=============================="
printf "현재 달러 환율: %.2f원\n" "$current_rate"
printf "최근 1주일 평균 환율: %.2f원\n" "$week_avg"
