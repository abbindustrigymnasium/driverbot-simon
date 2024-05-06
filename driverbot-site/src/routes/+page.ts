// /** @type {import('./$types').PageLoad} */
// export async function load({ fetch }) {
//   // attempt to start broker on page load
//   try {
//     const response = await fetch("/api/MQTT/broker/start", {
//       method: "PUT",
//       headers: {
//         "Content-Type": "application/json",
//       },
//       body: JSON.stringify({}),
//     });

//     if (!response.ok) {
//       throw new Error("Failed to start broker");
//     }

//     console.log("Broker running");
//   } catch (error) {
//     console.error(error);
//   }

//   return {};
// }
