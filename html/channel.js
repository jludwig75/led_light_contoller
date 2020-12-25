app.component('channel-view', {
    template:
    /*html*/
`
<div class="channel-view">
    <fieldset>
        <legend>Channel {{ channel_number }} Mode</legend>
        <form>
            <span v-for="supportedMode in supportedModes">
                <input type="radio" :id="supportedMode + channel_number" v-model="mode" :value="supportedMode" v-on:change="modeSelected">
                <label :for="supportedMode + channel_number">{{ supportedMode }}</label>
                <br/>
            </span>
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
            console.log('Got channel modes ' + this.supportedModes);
        },
        gotMode(mode) {
            this.mode = mode;
            console.log('Got channel ' + this.channel_number + ' mode: ' + this.mode);
        },
        getMode() {
            console.log('Getting channel ' + this.channel_number + ' mode');
            axios.
                get('/mode?channel=' + this.channel_number).
                then(response => this.gotMode(response.data)).
                catch(error => console.log('Failed to get station mode: ' + error));
        },
        handleSetModeSuccess() {
            console.log('Successfully set channel ' + this.channel_number + ' mode to ' + this.mode);
            this.getMode();
        },
        handleSetModeError(error) {
            var message = 'Failed to change channel mode to ' + this.mode + ': ' + error;
            console.log(message);
            this.getMode(); // Try to get the mode again
            alert(message);
        },
        modeSelected() {
            console.log('Setting channel ' + this.channel_number + ' mode to ' + this.mode);
            axios.
                post('/mode?channel=' + this.channel_number + '&mode=' + this.mode).
                then(response => this.handleSetModeSuccess()).
                catch(error => this.handleSetModeError());
        }
    },
    mounted() {
        console.log('Getting supported channel modes');
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
