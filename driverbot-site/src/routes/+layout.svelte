<script lang="ts">
  import Navigation from "$lib/components/Navigation.svelte";
</script>

<main>
  <Navigation />
  <slot />
</main>

<style>
  main {
    position: absolute;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    margin: 0 auto;
    overflow: hidden;
    box-sizing: border-box;
    background-color: #36393f;
    font-family: sans-serif;
    overflow: hidden;
  }
</style>
