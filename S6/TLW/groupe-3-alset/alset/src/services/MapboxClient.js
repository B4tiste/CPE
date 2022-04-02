/**
 * @typedef {Object} GetCoordsFeatureResponse
 * @property {number[]} center 
 */

/**
 * 
 * @typedef  {Object} GetCoordsResponse 
 * @property {GetCoordsFeatureResponse[]} features
 */

export class MapboxClient {
    /**
     * 
     * @param {string} accessToken 
     */
    constructor(accessToken) {
      this.accessToken = accessToken;
    }

    /**
     * 
     * @param {string} place 
     * @return {Promise<GetCoordsResponse>} 
     */
    async getCoords(place) {
        // Mapbox API request : https://api.mapbox.com/geocoding/v5/mapbox.places/{search_text}.json?access_token={access_token}
        const url =
          "https://api.mapbox.com/geocoding/v5/mapbox.places/" +
          place +
          ".json?access_token=" +
          this.accessToken;
        const response = await fetch(url);
        if(response.ok) {
          return response.json();
        }
        const text = await response.text();
        throw new Error(text);
    }
}
/**
 * @type {MapboxClient}
 */
export default new MapboxClient(process.env.VUE_APP_MAPBOX_ACCESS_TOKEN);