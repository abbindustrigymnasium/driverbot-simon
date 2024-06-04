<script lang="ts">
  import Navigation from "$lib/components/Navigation.svelte";
</script>

<main>
  <Navigation />
  <slot />
</main>

<style>
  main {
    margin: 0 auto;
    height: 100vh;
    overflow: hidden;
    box-sizing: border-box;
    background-color: #36393f;
    font-family: sans-serif;
  }
</style>
