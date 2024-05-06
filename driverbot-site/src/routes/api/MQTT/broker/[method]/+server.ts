import startBroker from "$lib/server/startBroker";
import { json } from "@sveltejs/kit";
import {
  setServerStore,
  getServerStore,
  clearServerStore,
} from "$lib/server/brokerStore";

type PostRequest = { request: Request; params: { method: string } };

export async function PUT({ request, params }: PostRequest) {
  const { method } = params;

  let response;
  let apiStatus = 500;
  // Check if the method is start
  if (method) {
    const functionResult = await handleStartServer();
    response = functionResult.response;
    apiStatus = functionResult.apiStatus;
  } else {
    response = { response: "Invalid method" };
    apiStatus = 400;
  }

  return json(response, { status: apiStatus });
}

const handleStartServer = async () => {
  // check if the broker is already running
  const broker = getServerStore();
  if (broker) {
    return { response: "Broker already running", apiStatus: 200 };
  }
  // start the broker
  const { apiStatus, server } = await startBroker();
  let response;
  if (apiStatus === 200) {
    setServerStore(server as any);
  } else {
    response = "Failed to start broker";
  }
  return { response, apiStatus };
};

const handleStopServer = () => {
  // retrieve the broker state and stop it
  const broker = getServerStore();
  if (!broker) {
    return { response: "Broker not running", success: false };
  }
  try {
    broker.close(() => {
      console.log("Broker stopped");
      clearServerStore();
    });
    return { response: "Broker stopped", success: true };
  } catch (error) {
    return { response: "Failed to stop broker", success: false };
  }
};
