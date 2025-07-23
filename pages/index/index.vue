<template>
	<view>
		<view class="log-container">
		      <text>{{ msg }}</text>
		</view>
		<button type="primary" @click="ClearMsg">ClearMsg</button>
		<button type="primary" @click="onGetRegistrationId">getRegistrationId</button>
		<button type="primary" @click="onAddTag">addTag</button>
		<button type="primary" @click="onGetTags">getTags</button>
		<button type="primary" @click="onSetAlias">setAlias</button>
		<button type="primary" @click="onDeleteAlias">deleteAlias</button>
		<button type="primary" @click="onGetAlias">getAlias</button>
	</view>
</template>

<script setup>
	// #ifdef APP-HARMONY
	import {
		ref
	} from 'vue';
	import {
		setDebug,
		setAppKey,
		setChannel,
		init,
		getRegistrationId,
		setEventCallBack,
		EventCallBackParams,
		EventCallBack,
		addTags,
		getTags,
		setAlias,
		deleteAlias,
		getAlias
	} from "@/uni_modules/jg-jpush-u"

	let msg = ref("HARMONY\n");


	console.log("JPUSH-", 'push vue');

	setEventCallBack({
		callback: (res) => {
			msg.value += JSON.stringify(res) + "\n";
			console.log("JPUSH-", 'push vue callback eventName:' + res.eventName);
			console.log("JPUSH-", 'push vue callback eventData:' + res.eventData);
		}
	})
	
	init();
	
	
	let ClearMsg=()=>{msg.value="clearMsg\n"}
	
	let onGetRegistrationId=()=>{
		let a = getRegistrationId();
		console.log("JPUSH-", 'push vue getRegistrationId:' + JSON.stringify(a));
		msg.value += JSON.stringify(a) + "\n";
	}
	let onAddTag=()=>{
		addTags(1,["ab","cd"])
	}
	let onGetTags=()=>{
		getTags(2,1)
	}
	
	let onSetAlias=()=>{
		setAlias(3,"jjjjjj")
	}
	let onDeleteAlias=()=>{
		deleteAlias(4)
	}
	let onGetAlias=()=>{
		getAlias(5)
	}
	
	
	// #endif
</script>

<style>

</style>