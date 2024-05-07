<script lang="ts">
  import { FontAwesomeIcon } from "@fortawesome/svelte-fontawesome";
  import { scale } from "svelte/transition";
  import {
    faHome,
    faInfoCircle,
    faGamepad,
  } from "@fortawesome/free-solid-svg-icons";
  import { page } from "$app/stores";

  let hoveredItem = "";
  let selectedItem = "Home";

  // Set the selected item based on the current route
  $: switch ($page.route.id) {
    case "/":
      selectedItem = "Home";
      break;
    case "/about":
      selectedItem = "About";
      break;
    case "/controller":
      selectedItem = "Controller";
      break;
  }

  const navItems = [
    { name: "Home", icon: faHome, route: "/" },
    { name: "About", icon: faInfoCircle, route: "/about" },
    { name: "Controller", icon: faGamepad, route: "/controller" },
  ];
</script>

<nav>
  <!-- Display all the items in the navItems map -->
  {#each navItems as item (item.route)}
    <li
      class:selected={selectedItem === item.name}
      on:mouseenter={() => (hoveredItem = item.name)}
      on:mouseleave={() => (hoveredItem = "")}
    >
      <a href={item.route} class:selected={selectedItem === item.name}>
        <!-- Display text instead of image when hovered -->
        {#if hoveredItem === item.name}
          <div class="item-name-wrapper" transition:scale={{ duration: 700 }}>
            {item.name}
          </div>
        {:else}
          <div transition:scale={{ duration: 700 }}>
            <FontAwesomeIcon icon={item.icon} />
          </div>
        {/if}
      </a>
    </li>
  {/each}
</nav>

<style>
  /* The main navigation bar */
  nav {
    position: absolute;
    left: 0;
    width: 72px;
    height: 100%;
    background: #2f3136;
    display: flex;
    align-items: center;
    flex-direction: column;
  }

  /* Styles for the navigation items */
  a,
  li {
    text-decoration: none;
    list-style-type: none;
    width: 56px;
    height: 56px;
    margin: 4px;
    color: #fff;
    display: flex;
    align-items: center;
    justify-content: center;
    background: #7289d9;
    border-radius: 12px;
    font-size: 32px;
  }

  /* Styles for the item name wrapper */
  .item-name-wrapper {
    font-size: 12px;
  }

  /* Styles for the anchor tags */
  a {
    position: relative;
  }

  /* Styles for the div inside the anchor tags */
  a > div {
    position: absolute;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  /* Styles for the selected item */
  .selected {
    background: #000;
  }
</style>