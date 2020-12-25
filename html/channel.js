app.component('channel-view', {
    template:
    /*html*/
`
<div class="channel-view">
    <fieldset>
        <legend><h3>Channel {{ channel_number }} Mode</h3></legend>
        <form>
            <ul class="channel-mode-list">
                <li v-for="supportedMode in supportedModes">
                    <input type="radio" :id="supportedMode + channel_number" v-model="mode" :value="supportedMode" v-on:change="modeSelected">
                    <label :for="supportedMode + channel_number">{{ supportedMode }}</label>
                    <br/>
                </li>
            </ul>
        </form>
    </fieldset>
</div>
`,
    props: {
        channel_number: {
            type: Number,
            required: true
        }
    },
    data() {
        return {
            supportedModes: [],
            mode: null,
            polling: null
        }
    },
    methods: {
        gotModes(modeList) {
            this.supportedModes = modeList;
        },
        gotMode(mode) {
            this.mode = mode;
        },
        getMode() {
            axios.
                get('/mode?channel=' + this.channel_number).
                then(response => this.gotMode(response.data)).
                catch(error => console.log('Failed to get station mode: ' + error));
        },
        handleSetModeSuccess() {
            this.getMode();
        },
        handleSetModeError(error) {
            this.mode = null;
            var message = 'Failed to change channel mode to ' + this.mode + ': ' + error;
            console.error(message);
            this.getMode(); // Try to get the mode again
            alert(message);
        },
        modeSelected() {
            axios.
                post('/mode?channel=' + this.channel_number + '&mode=' + this.mode).
                then(response => this.handleSetModeSuccess()).
                catch(error => this.handleSetModeError());
        }
    },
    mounted() {
        axios.
            get('/supported_modes').
            then(response => this.gotModes(response.data)).
            catch(error => console.log('Failed to get mode list: ' + error));
        this.getMode();
        this.polling = setInterval(this.getMode, 1000);
    },
    beforeUnmount() {
        clearInterval(this.polling);
    }
});
