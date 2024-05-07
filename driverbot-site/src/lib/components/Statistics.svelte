<script lang="ts">
</script>

<div class="statistics">
  <h1 class="main-label custom-shadow">Statistics</h1>
  <div class="statistic">
    <div class="label custom-shadow">Speed:</div>
    <div class="statistic-value">
      5km/h
    </div>
  </div>
  <div class="statistic">
    <div class="label custom-shadow">RPM: </div>
    <div class="statistic-value">
      60
    </div>
  </div>
  <div class="statistic bottom">
    <div class="label custom-shadow">Status: </div>
    <div class="statistic-value">
      Active
    </div>
  </div>
</div>

<style>
  .statistics {
    margin-bottom: 32px;
    position: relative;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-direction: column;
    padding: 0 24px 0 24px;
    left: 16px;
    top: 16px;
    border-radius: 8px;
    background: #2f3136;
    box-shadow: 6px 8px 5px rgba(0, 0, 0, 0.2);
    width: 192px;
  }

  .statistic {
    display: flex;
    align-items: center;
    justify-content: center;
    margin: 16px;
  }

  .statistic-value {
    color: #fff;
    position: absolute;
    right: 12px;
  }

  .label {
    font-size: 18px;
    position: absolute;
    left: 12px;
    color: #fff;
  }

  .main-label {
    margin: 12px 0 20px 0;
    color: #fff;
  }

  .custom-shadow {
    text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2);
  }

  .bottom {
    margin-bottom: 24px;
  }
</style>
