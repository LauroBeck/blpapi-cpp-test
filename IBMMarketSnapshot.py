from dataclasses import dataclass
from typing import Tuple, List
import matplotlib.pyplot as plt

@dataclass
class AnalystTargets:
    average: float
    low: float
    high: float

@dataclass
class DividendInfo:
    quarterly: float
    yield_pct: float
    record_date: str

@dataclass
class MarketSnapshot:
    symbol: str
    price: float
    daily_low: float
    pct_change: float
    monthly_trend_pct: float
    rating: str
    targets: AnalystTargets
    dividend: DividendInfo
    strategic_focus: Tuple[str, ...]

def print_snapshot(s: MarketSnapshot):
    print("\n================ IBM MARKET SNAPSHOT ================\n")
    print(f"Symbol: {s.symbol}")
    print(f"Price: ${s.price}")
    print(f"Daily Low: ${s.daily_low}")
    print(f"Change: {s.pct_change:+.2f}%")
    print(f"Recent Trend: {s.monthly_trend_pct:.2f}%\n")

    print("Analyst Sentiment")
    print(f"Rating: {s.rating}")
    print(
        f"Targets → Avg: ${s.targets.average} | "
        f"Low: ${s.targets.low} | High: ${s.targets.high}\n"
    )

    print("Dividends")
    print(f"Quarterly Dividend: ${s.dividend.quarterly}")
    print(f"Yield: {s.dividend.yield_pct:.2f}%")
    print(f"Record Date: {s.dividend.record_date}\n")

    print("Strategic Focus")
    for item in s.strategic_focus:
        print(f"• {item}")

    print("\n=====================================================\n")

# -----------------------------------------------------
# Data based on your description
# -----------------------------------------------------

snapshot = MarketSnapshot(
    symbol="IBM",
    price=257.16,
    daily_low=253.80,
    pct_change=0.34,
    monthly_trend_pct=-11.0,
    rating="Hold (Downgraded Feb 18, 2026)",
    targets=AnalystTargets(
        average=320.38,
        low=218.00,
        high=380.00
    ),
    dividend=DividendInfo(
        quarterly=1.68,
        yield_pct=2.6,
        record_date="2026-02-10"
    ),
    strategic_focus=(
        "Artificial Intelligence",
        "Quantum Computing",
        "Quantum Advantage target by end of 2026",
        "FlashSystem with agentic AI"
    )
)

print_snapshot(snapshot)

@dataclass
class PartnersProjections:
    revenue_growth_pct: float
    market_share_pct: float
    partner_ecosystem_score: int
    projected_deals_count: int

cloud_partners_projections = PartnersProjections(
    revenue_growth_pct=15.5,
    market_share_pct=8.2,
    partner_ecosystem_score=92,
    projected_deals_count=1200
)

def print_partners_projections(projections: PartnersProjections):
    print("\n================ IBM CLOUD PARTNERS PROJECTIONS ================\n")
    print(f"Revenue Growth: {projections.revenue_growth_pct:.2f}%")
    print(f"Market Share: {projections.market_share_pct:.2f}%")
    print(f"Partner Ecosystem Score: {projections.partner_ecosystem_score}")
    print(f"Projected Deals Count: {projections.projected_deals_count}")
    print("\n================================================================\n")

print_partners_projections(cloud_partners_projections)

fig, axes = plt.subplots(1, 2, figsize=(14, 6))
fig.suptitle('IBM Cloud Partners Projections Overview', fontsize=16)

# --- Plot 1: Revenue Growth ---
metrics_growth = ['Revenue Growth']
values_growth = [cloud_partners_projections.revenue_growth_pct]

axes[0].bar(metrics_growth, values_growth, color='skyblue')
axes[0].set_ylabel('Percentage (%)')
axes[0].set_title('Projected Revenue Growth')
axes[0].set_ylim(0, max(values_growth) * 1.2)
axes[0].grid(axis='y', linestyle='--', alpha=0.7)
for i, value in enumerate(values_growth):
    axes[0].text(i, value + 0.5, f'{value:.2f}%', ha='center', va='bottom', fontsize=10)

# --- Plot 2: Projected Deals Count ---
metrics_deals = ['Projected Deals Count']
values_deals = [cloud_partners_projections.projected_deals_count]

axes[1].bar(metrics_deals, values_deals, color='lightgreen')
axes[1].set_ylabel('Count')
axes[1].set_title('Projected Deals Count')
axes[1].set_ylim(0, max(values_deals) * 1.2)
axes[1].grid(axis='y', linestyle='--', alpha=0.7)
for i, value in enumerate(values_deals):
    axes[1].text(i, value + 0.05 * max(values_deals), f'{int(value)}', ha='center', va='bottom', fontsize=10)

plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # Adjust layout to prevent suptitle overlap
plt.show()
