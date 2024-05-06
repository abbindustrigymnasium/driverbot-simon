export default async function (direction: string,) {
  try {
    const response = await fetch(`/api/MQTT/publish`, {
      method: "POST",
      body: JSON.stringify({
        topic: "simon.svoboda@hitachigymnasiet.se/direction",
        message: direction,
      }),
      headers: {
        "Content-Type": "application/json",
      },
    });
    return response;
  } catch (e) {
    console.error(e);
    return e;
  }
}
