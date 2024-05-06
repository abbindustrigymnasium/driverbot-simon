// Utility function to start or stop the MQTT broker on the backend

export default async function (method: string) {
  try {
    const response = await fetch(`/api/MQTT/broker/${method}`, {
      method: "POST",
      body: JSON.stringify({}),
      headers: {
        "Content-Type": "application/json",
      },
    });

    const data = await response.json();
    return { response, data };
  } catch (e) {
    return e;
  }
}
