<script lang="ts">
  import Navigation from "$lib/components/Navigation.svelte";
  import { onMount } from "svelte";

  import "bootstrap/dist/css/bootstrap.min.css";

  // Try to start the broker on mount
  onMount(async () => {
    try {
      const response = await fetch("/api/MQTT/broker/start", {
        method: "PUT",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({}),
      });

      if (!response.ok) {
        throw new Error("Failed to start broker");
      }

      console.log("Broker running");
    } catch (error) {
      console.error(error);
    }
  });
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
  }
</style>
