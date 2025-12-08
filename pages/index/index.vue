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
		<button type="primary" @click="onSetBadgeNumber">setBadgeNumber(5)</button>
		<button type="primary" @click="onResetBadge">resetBadge</button>
		<button type="primary" @click="onGetBadgeNumber">getBadgeNumber</button>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	// import {
	// 	init as initXiaomi
	// } from "@/uni_modules/jg-jpush-u-xiaomi"
	// import {
	// 	init as initHuawei
	// } from "@/uni_modules/jg-jpush-u-huawei"
	// import {
	// 	init as initFcm
	// } from "@/uni_modules/jg-jpush-u-fcm"
	// import {
	// 	init as initNio
	// } from "@/uni_modules/jg-jpush-u-nio"
	// import {
	// 	init as initHonor
	// } from "@/uni_modules/jg-jpush-u-honor"
	// import {
	// 	init as initMeizu
	// } from "@/uni_modules/jg-jpush-u-meizu"
	// import {
	// 	init as initOppo
	// } from "@/uni_modules/jg-jpush-u-oppo"
	// import {
	// 	init as initVivo
	// } from "@/uni_modules/jg-jpush-u-vivo"

	import {
		init,
		setDebug,
		setChannel,
		initPush,
		getRegistrationId,
		setEventCallBack,
		addTags,
		setAlias,
		deleteAlias,
		getAlias,
		setBadgeNumber,
		resetBadge,
		getBadgeNumber
	} from "@/uni_modules/jg-jpush-u"

	// #ifdef APP-PLUS
	import {
		getAllTags
	} from "@/uni_modules/jg-jpush-u"
	// #endif

	// #ifdef APP-HARMONY
	import {
		getTags
	} from "@/uni_modules/jg-jpush-u"
	// #endif


	let msg = ref(uni.getSystemInfoSync().platform + "\n");


	console.log("JPUSH-", 'push vue');

	setEventCallBack({
		callback: (res) => {
			msg.value += JSON.stringify(res) + "\n";
			console.log("JPUSH-", 'push vue callback eventName:' + res.eventName);
			console.log("JPUSH-", 'push vue callback eventData:' + res.eventData);
		}
	})
	
	setDebug(true)
	if(uni.getSystemInfoSync().platform !== "ios"){
		init()
	}else{
		initPush({
			appkey: "4fcc3e237eec4c4fb804ad49",
			channel: "demo",
			isProduction: false,
			advertisingId:""
		})
	}



	let ClearMsg = () => {
		msg.value = "clearMsg\n"
	}

	let onGetRegistrationId = () => {
		let a = getRegistrationId();
		console.log("JPUSH-", 'push vue getRegistrationId:' + JSON.stringify(a));
		msg.value += JSON.stringify(a) + "\n";
	}
	let onAddTag = () => {
		addTags(1, ["ab", "cd"])
	}
	let onGetTags = () => {
		// #ifdef APP-PLUS
		getAllTags(2)
		// #endif

		// #ifdef APP-HARMONY
		getTags(2, 1)
		// #endif
	}

	let onSetAlias = () => {
		setAlias(3, "jjjjjj")
	}
	let onDeleteAlias = () => {
		deleteAlias(4)
	}
	let onGetAlias = () => {
		getAlias(5)
	}
	
	let onSetBadgeNumber = () => {
		setBadgeNumber(5)
		msg.value += "setBadgeNumber(5)\n"
		console.log("JPUSH-", 'setBadgeNumber(5)')
	}
	
	let onResetBadge = () => {
		resetBadge()
		msg.value += "resetBadge\n"
		console.log("JPUSH-", 'resetBadge')
	}
	
	let onGetBadgeNumber = () => {
		if(uni.getSystemInfoSync().platform !== "ios"){
			console.log("JPUSH- do not support")
		}else {
			let badge = getBadgeNumber()
			msg.value += "getBadgeNumber: " + badge + "\n"
			console.log("JPUSH-", 'getBadgeNumber: ' + badge)
		}
	}
</script>

<style>

</style>